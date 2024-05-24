#include "Evaluator.hpp"

using namespace dplsrc;

void Evaluator::initStdlib() {
    Procedure::ProcType print1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        std::cout << args[0]->getVal().toString() << '\n';
        return nullptr;
    };

    Procedure::ProcType input0 =
        []([[maybe_unused]] const std::vector<std::shared_ptr<AstNode>> &args) {
            std::string inputStr;
            std::getline(std::cin, inputStr);
            return inputStr;
        };

    Procedure::ProcType input1 = [input0](std::vector<std::shared_ptr<AstNode>> args) {
        std::cout << args[0]->getVal().toString();
        return input0(args);
    };

    Procedure::ProcType type1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        return args[0]->getVal().toTypeString();
    };

    Procedure::ProcType str1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        return args[0]->getVal().toString();
    };

    Procedure::ProcType int1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        if (args[0]->getVal().is<Value::INT>()) {
            return args[0]->getVal().get<Value::INT>();
        }

        if (args[0]->getVal().is<Value::FLOAT>()) {
            return static_cast<Value::INT>(args[0]->getVal().get<Value::FLOAT>());
        }

        if (args[0]->getVal().is<Value::BOOL>()) {
            return static_cast<Value::INT>(args[0]->getVal().get<Value::BOOL>());
        }

        if (args[0]->getVal().is<Value::STR>()) {
            try {
                return std::stol(args[0]->getVal().get<Value::STR>());
            } catch (const std::invalid_argument &e) {
                throw RuntimeException("Could not convert string to int");
            }
        }

        throw RuntimeException("Could not convert value to int");
    };

    Procedure::ProcType float1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        if (args[0]->getVal().is<Value::INT>()) {
            return static_cast<Value::FLOAT>(args[0]->getVal().get<Value::INT>());
        }
        if (args[0]->getVal().is<Value::FLOAT>()) {
            return args[0]->getVal().get<Value::FLOAT>();
        }
        if (args[0]->getVal().is<Value::BOOL>()) {
            return static_cast<Value::FLOAT>(args[0]->getVal().get<Value::BOOL>());
        }
        if (args[0]->getVal().is<Value::STR>()) {
            try {
                return std::stod(args[0]->getVal().get<Value::STR>());
            } catch (const std::invalid_argument &e) {
                throw RuntimeException("Could not convert string to float");
            }
        }

        throw RuntimeException("Could not convert value to float");
    };

    Procedure::ProcType bool1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        if (args[0]->getVal().is<Value::INT>()) {
            return static_cast<Value::BOOL>(args[0]->getVal().get<Value::INT>());
        }
        if (args[0]->getVal().is<Value::FLOAT>()) {
            return static_cast<Value::BOOL>(args[0]->getVal().get<Value::FLOAT>());
        }
        if (args[0]->getVal().is<Value::BOOL>()) {
            return args[0]->getVal().get<Value::BOOL>();
        }

        throw RuntimeException("Could not convert value to bool");
    };

    Procedure::ProcType list1 = [this](std::vector<std::shared_ptr<AstNode>> args) {
        if (args[0]->getVal().is<Value::COLUMN>()) {
            return copyList(args[0]->getVal().get<Value::COLUMN>()->data);
        }
        throw RuntimeException("Could not convert value to list");
    };

    Procedure::ProcType sum1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();
        if (val.is<Value::LIST>() || val.is<Value::COLUMN>()) {
            Value::LIST list =
                (val.is<Value::LIST>()) ? val.get<Value::LIST>() : val.get<Value::COLUMN>()->data;
            Value::FLOAT sum = 0.0;
            for (const std::shared_ptr<Value> &elem : *list) {
                sum += elem->getNumericValue();
            }
            return Value(sum);
        }
        throw RuntimeException("Cannot sum values of type " + val.toTypeString());
    };

    Procedure::ProcType mean1 = [sum1](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();
        if (val.is<Value::LIST>() || val.is<Value::COLUMN>()) {
            Value::LIST list =
                (val.is<Value::LIST>()) ? val.get<Value::LIST>() : val.get<Value::COLUMN>()->data;
            return Value(sum1(args).get<Value::FLOAT>() / list->size());
        }

        throw RuntimeException("Cannot get mean of values of type " + val.toTypeString());
    };

    Procedure::ProcType stdev1 = [mean1](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();
        if (val.is<Value::LIST>() || val.is<Value::COLUMN>()) {
            Value::LIST list =
                (val.is<Value::LIST>()) ? val.get<Value::LIST>() : val.get<Value::COLUMN>()->data;
            Value::FLOAT mu = mean1(args).get<Value::FLOAT>();
            Value::FLOAT sum = 0.0;
            for (const std::shared_ptr<Value> &elem : *list) {
                sum += std::pow(elem->getNumericValue() - mu, 2);
            }
            return Value(std::sqrt(sum / list->size()));
        }

        throw RuntimeException("Cannot get standard deviation of values of type " +
                               val.toTypeString());
    };

    Procedure::ProcType len1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();

        if (val.is<Value::STR>()) {
            return static_cast<Value::INT>(val.get<Value::STR>().size());
        }
        if (val.is<Value::LIST>()) {
            return static_cast<Value::INT>(val.get<Value::LIST>()->size());
        }
        if (val.is<Value::TABLE>()) {
            return static_cast<Value::INT>(val.get<Value::TABLE>()->second.size());
        }
        if (val.is<Value::COLUMN>()) {
            return static_cast<Value::INT>(val.get<Value::COLUMN>()->data->size());
        }

        throw RuntimeException("Len called with invalid type " + val.toTypeString() + '\n');
    };

    Procedure::ProcType ceil1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();

        if (val.is<Value::FLOAT>()) {
            return static_cast<Value::INT>(std::ceil(val.get<Value::FLOAT>()));
        }
        if (val.is<Value::INT>()) {
            return val.get<Value::INT>();
        }

        throw RuntimeException("Ceil called with invalid type " + val.toTypeString() +
                               ". Expected: " + Value(0.0).toTypeString());
    };

    Procedure::ProcType floor1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();

        if (val.is<Value::FLOAT>()) {
            return static_cast<Value::INT>(std::floor(val.get<Value::FLOAT>()));
        }
        if (val.is<Value::INT>()) {
            return val.get<Value::INT>();
        }

        throw RuntimeException("Floor called with invalid type " + val.toTypeString() +
                               ". Expected: " + Value(0.0).toTypeString());
    };

    Procedure::ProcType round1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();

        if (val.is<Value::FLOAT>()) {
            return static_cast<Value::INT>(std::round(val.get<Value::FLOAT>()));
        }
        if (val.is<Value::INT>()) {
            return val.get<Value::INT>();
        }

        throw RuntimeException("Round called with invalid type " + val.toTypeString() +
                               ". Expected: " + Value(0.0).toTypeString());
    };

    Procedure::ProcType copy1 = [this](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();
        if (val.is<Value::LIST>()) {
            return Value(copyList(val.get<Value::LIST>()));
        }
        if (val.is<Value::TABLE>()) {
            return Value(copyTable(val.get<Value::TABLE>()));
        }

        throw RuntimeException("Copy called with invalid type " + val.toTypeString());
    };

    Procedure::ProcType readFile1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value fileName = args[0]->getVal();

        if (!fileName.is<Value::STR>()) {
            throw RuntimeException("ReadFile called with invalid type " + fileName.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        std::filesystem::path filePath = fileName.get<Value::STR>();
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw RuntimeException("Could not open file \"" + fileName.toString() + "\"");
        }

        std::string fileContents((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());

        return fileContents;
    };

    Procedure::ProcType writeFile2 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value fileName = args[0]->getVal();
        Value content = args[1]->getVal();

        if (!content.is<Value::STR>() || !fileName.is<Value::STR>()) {
            throw RuntimeException("WriteFile called with invalid types");
        }

        std::filesystem::path filePath = fileName.get<Value::STR>();
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw RuntimeException("Could not open file \"" + fileName.get<Value::STR>() + "\"");
        }

        file << content.get<Value::STR>();

        return nullptr;
    };

    Procedure::ProcType readTable3 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value fileName = args[0]->getVal();
        Value delimiterVal = args[1]->getVal();
        Value dataTypesVal = args[2]->getVal();

        if (!fileName.is<Value::STR>()) {
            throw RuntimeException("ReadTable called with invalid type " + fileName.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (!delimiterVal.is<Value::STR>()) {
            throw RuntimeException("ReadTable called with invalid type " +
                                   delimiterVal.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (delimiterVal.get<Value::STR>().size() != 1) {
            throw RuntimeException("Delimiter must be a string of size 1");
        }

        if (!dataTypesVal.is<Value::LIST>()) {
            throw RuntimeException("ReadTable called with invalid type " +
                                   dataTypesVal.toTypeString() +
                                   ". Expected: " + Value({}).toTypeString() + '\n');
        }

        char delimiter = delimiterVal.get<Value::STR>()[0];
        std::filesystem::path filePath = fileName.get<Value::STR>();
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw RuntimeException("Could not open file \"" + fileName.toString() + "\"");
        }

        bool isFirstLine = true;
        std::string line;
        Value::TABLE table = std::make_shared<
            std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();
        std::vector<Value::COLUMN> cols;
        std::vector<Value::STR> headers;
        while (std::getline(file, line)) {
            // Split line by delimiterstd::unordered_map
            bool inQuotes = false;
            std::vector<Value::STR> values;
            Value::STR value;
            for (char c : line) {
                if (c == '"') {
                    inQuotes = !inQuotes;
                } else if (c == delimiter && !inQuotes) {
                    values.push_back(value);
                    value.clear();
                } else {
                    value += c;
                }
            }

            if (!value.empty()) {
                values.push_back(value);
            }

            // If first line we store as headers
            if (isFirstLine) {
                isFirstLine = false;
                headers = values;

                // Initialize columns
                for (size_t i = 0; i < headers.size(); ++i) {
                    cols.emplace_back(std::make_shared<Value::COL_STRUCT>());
                    cols[i]->data = std::make_shared<std::vector<std::shared_ptr<Value>>>();
                }
            } else {
                for (size_t i = 0; i < headers.size(); ++i) {
                    if (i >= values.size() || values[i].empty()) {
                        cols[i]->data->emplace_back(std::make_shared<Value>(nullptr));
                    } else {
                        const Value::LIST &dataTypes = dataTypesVal.get<Value::LIST>();
                        if (dataTypes->empty()) {
                            cols[i]->data->emplace_back(std::make_shared<Value>(values[i]));
                        } else {
                            Value::STR dataType = dataTypes->at(i)->get<Value::STR>();
                            if (dataType == "int") {
                                try {
                                    cols[i]->data->emplace_back(
                                        std::make_shared<Value>(std::stol(values[i])));
                                } catch (const std::out_of_range &e) {
                                    throw RuntimeException("Integer value out of range");
                                }
                            } else if (dataType == "float") {
                                cols[i]->data->emplace_back(
                                    std::make_shared<Value>(std::stod(values[i])));
                            } else if (dataType == "bool") {
                                bool isTrue = values[i] != "False" && values[i] != "0";
                                cols[i]->data->emplace_back(std::make_shared<Value>(isTrue));
                            } else if (dataType == "NoneType") {
                                cols[i]->data->emplace_back(std::make_shared<Value>(nullptr));
                            } else if (dataType == "str") {
                                cols[i]->data->emplace_back(std::make_shared<Value>(values[i]));
                            } else if (dataType == "list") {
                                throw RuntimeException(
                                    "Type \"lists\" not supported when loading table from file");
                            } else if (dataType == "table") {
                                throw RuntimeException(
                                    "Type \"table\" not supported when loading table from file");
                            } else if (dataType == "column") {
                                throw RuntimeException(
                                    "Data can not be explicitly converted to type \"column\"");
                            } else {
                                throw RuntimeException("Trying to convert to invalid data type \"" +
                                                       dataType + "\"");
                            }
                        }
                    }

                    // If header is missing then we generate a default one to ensure uniqueness
                    if (headers[i].empty()) {
                        std::hash<std::size_t> hash;
                        std::string hashStr = "id" + std::to_string(hash(i));

                        // While the hash is already in headers vector we make a new one to avoid
                        // collision
                        size_t j = i;
                        while (std::count(headers.begin(), headers.end(), hashStr) != 0) {
                            ++j;
                            hashStr = "id" + std::to_string(hash(j));
                        }

                        headers[i] = hashStr;
                    }

                    cols[i]->header = headers[i];
                    cols[i]->parent = table;
                }
            }
        }

        // Insert columns into table
        for (size_t i = 0; i < headers.size(); ++i) {
            table->first.emplace_back(headers[i]);
            table->second.insert({headers[i], cols[i]});
        }

        return table;
    };

    Procedure::ProcType readTable2 = [readTable3](std::vector<std::shared_ptr<AstNode>> args) {
        std::shared_ptr<LeafNode> dataTypes = std::make_shared<LeafNode>(nullptr);
        dataTypes->setVal(std::make_shared<std::vector<std::shared_ptr<Value>>>());
        args.emplace_back(dataTypes);
        return readTable3(args);
    };

    Procedure::ProcType readTable1 = [readTable2](std::vector<std::shared_ptr<AstNode>> args) {
        std::shared_ptr<LeafNode> delim = std::make_shared<LeafNode>(nullptr);
        delim->setVal(Value(","));
        args.emplace_back(delim);
        return readTable2(args);
    };

    Procedure::ProcType writeTable3 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value fileName = args[0]->getVal();
        Value table = args[1]->getVal();
        Value delimiterVal = args[2]->getVal();

        if (!fileName.is<Value::STR>()) {
            throw RuntimeException("WriteTable called with invalid type " +
                                   fileName.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (!table.is<Value::TABLE>()) {
            throw RuntimeException("WriteTable called with invalid type " + table.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (!delimiterVal.is<Value::STR>()) {
            throw RuntimeException("WriteTable called with invalid type " +
                                   delimiterVal.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (delimiterVal.get<Value::STR>().size() != 1) {
            throw RuntimeException("Delimiter must be a string of size 1");
        }

        char delimiter = delimiterVal.get<Value::STR>()[0];

        std::filesystem::path filePath = fileName.get<Value::STR>();
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw RuntimeException("Could not open file \"" + fileName.toString() + "\"");
        }

        // Write headers
        for (const Value::STR &header : table.get<Value::TABLE>()->first) {
            file << header << delimiter;
        }

        // Overwrite last delimiter
        if (!table.get<Value::TABLE>()->second.empty()) {
            file.seekp(-1, std::ios_base::end);
        }

        file << '\n';

        // Write data
        for (size_t i = 0; i < table.get<Value::TABLE>()->second.begin()->second->data->size();
             ++i) {
            std::string entryStr;
            for (const Value::STR &key : table.get<Value::TABLE>()->first) {
                Value::STR val = (*table.get<Value::TABLE>()->second.at(key)->data)[i]->toString();
                entryStr += val + delimiter;
            }

            // Overwrite last delimiter
            if (!table.get<Value::TABLE>()->second.empty()) {
                entryStr.pop_back();
            }

            file << entryStr << '\n';
        }

        return nullptr;
    };

    Procedure::ProcType writeTable2 = [writeTable3](std::vector<std::shared_ptr<AstNode>> args) {
        std::shared_ptr<LeafNode> delim = std::make_shared<LeafNode>(nullptr);
        delim->setVal(Value(","));
        args.emplace_back(delim);
        return writeTable3(args);
    };

    ptable.bind(Procedure("print", {"msg"}, print1));
    ptable.bind(Procedure("input", {}, input0));
    ptable.bind(Procedure("input", {"msg"}, input1));
    ptable.bind(Procedure("type", {"x"}, type1));
    ptable.bind(Procedure("str", {"x"}, str1));
    ptable.bind(Procedure("int", {"x"}, int1));
    ptable.bind(Procedure("float", {"x"}, float1));
    ptable.bind(Procedure("bool", {"x"}, bool1));
    ptable.bind(Procedure("list", {"x"}, list1));
    ptable.bind(Procedure("sum", {"x"}, sum1));
    ptable.bind(Procedure("mean", {"x"}, mean1));
    ptable.bind(Procedure("stdev", {"x"}, stdev1));
    ptable.bind(Procedure("len", {"x"}, len1));
    ptable.bind(Procedure("ceil", {"x"}, ceil1));
    ptable.bind(Procedure("floor", {"x"}, floor1));
    ptable.bind(Procedure("round", {"x"}, round1));
    ptable.bind(Procedure("copy", {"x"}, copy1));
    ptable.bind(Procedure("readFile", {"filename"}, readFile1));
    ptable.bind(Procedure("writeFile", {"filename", "content"}, writeFile2));
    ptable.bind(Procedure("readTable", {"filename"}, readTable1));
    ptable.bind(Procedure("readTable", {"filename", "delimiter"}, readTable2));
    ptable.bind(Procedure("readTable", {"filename", "delimiter", "dataTypes"}, readTable3));
    ptable.bind(Procedure("writeTable", {"filename", "table"}, writeTable2));
    ptable.bind(Procedure("writeTable", {"filename", "table", "delimiter"}, writeTable3));
}
