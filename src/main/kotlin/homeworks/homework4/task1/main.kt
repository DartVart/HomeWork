package homeworks.homework4.task1

import homeworks.homework4.task1.hashFunctions.PolynomialHashFunction
import homeworks.homework4.task1.hashFunctions.SimpleHashFunction
import java.io.File
import java.io.FileNotFoundException

const val INITIAL_SIZE = 20
const val PATH_TO_TEXT_FILE = "./src/main/resources/homeworks/homework4/task1/input.txt"

fun safeReadLine(): String {
    var result = readLine()
    while (result == null) {
        println("An error occurred while entering a string. Please enter again.")
        result = readLine()
    }
    return result
}

enum class Actions(val code: String) {
    HELP("help"),
    ADD_TO_HASH_TABLE("add"),
    REMOVE_FROM_HASH_TABLE("remove"),
    PRINT_STATISTICS("print statistics"),
    FIND("find"),
    FILL_FORM_FILE("fill from file"),
    CHANGE_HASH_FUNCTION("change hash fun"),
    EXIT("exit");
}

enum class HashFunctions(val code: String) {
    SIMPLE("simple"),
    POLYNOMIAL("polynomial");
}

fun printIntroduction() {
    println("---------------------------HASH TABLE---------------------------")
    printHelp()
}

fun printHelp() {
    println("The following commands are supported:")
    println("1. \"${Actions.HELP.code}\" to see available commands;")
    println("2. \"${Actions.ADD_TO_HASH_TABLE.code}\" to add a value to the hash table;")
    println("3. \"${Actions.REMOVE_FROM_HASH_TABLE.code}\" to remove the entry from the hash table;")
    println("4. \"${Actions.PRINT_STATISTICS.code}\" to see basic statistics about the hash table;")
    println("5. \"${Actions.FIND.code}\" to find the value by key;")
    println("6. \"${Actions.FILL_FORM_FILE.code}\" to supplement the table with data from the file;")
    println("7. \"${Actions.CHANGE_HASH_FUNCTION.code}\" to change the hash function;")
    println("8. \"${Actions.EXIT.code}\" to exit.")
}

fun handleUserActions(hashTable: HashTable<String, String>, inputFile: File) {
    if (!inputFile.exists()) {
        throw FileNotFoundException("File \"${inputFile.path}\" not found.")
    }
    printIntroduction()
    println("Enter new command:")
    var currentCommand = safeReadLine()
    while (currentCommand != Actions.EXIT.code) {
        when (currentCommand) {
            Actions.CHANGE_HASH_FUNCTION.code -> handleChangeHashFunctionAction(hashTable)
            Actions.FILL_FORM_FILE.code -> hashTable.fileParser.fillFromFile(inputFile)
            Actions.FIND.code -> handleFindAction(hashTable)
            Actions.PRINT_STATISTICS.code -> hashTable.printStatistics()
            Actions.REMOVE_FROM_HASH_TABLE.code -> handleRemoveAction(hashTable)
            Actions.ADD_TO_HASH_TABLE.code -> handleAddAction(hashTable)
            Actions.HELP.code -> printHelp()
            else -> println("Incorrect command entered.")
        }
        println("Enter new command:")
        currentCommand = safeReadLine()
    }
}

fun handleAddAction(hashTable: HashTable<String, String>) {
    println("Enter a key:")
    val key = safeReadLine()
    println("Enter a value:")
    val value = safeReadLine()
    val isAdded = hashTable.add(key, value)
    if (isAdded) {
        println("This entry has been successfully added.")
    } else {
        println("This entry already exists.")
    }
}

fun handleRemoveAction(hashTable: HashTable<String, String>) {
    println("Enter a key:")
    val key = safeReadLine()
    val isDeleted = hashTable.remove(key)
    if (isDeleted) {
        println("This entry has been successfully removed.")
    } else {
        println("No such entry exists.")
    }
}

fun handleFindAction(hashTable: HashTable<String, String>) {
    println("Enter a key:")
    val key = safeReadLine()
    val resultValue = hashTable.find(key)
    if (resultValue == null) {
        println("There is no value in the table that matches the $key")
    } else {
        println("Value that matches the $key: ${hashTable.find(key)}")
    }
}

fun handleChangeHashFunctionAction(hashTable: HashTable<String, String>) {
    println("Enter \"${HashFunctions.POLYNOMIAL.code}\" to connect the polynomial hash function.")
    println("Enter \"${HashFunctions.SIMPLE.code}\" to connect the simple hash function.")
    var command: String?
    do {
        command = readLine()
        when (command) {
            HashFunctions.SIMPLE.code -> hashTable.setHashFunction(SimpleHashFunction())
            HashFunctions.POLYNOMIAL.code -> hashTable.setHashFunction(PolynomialHashFunction())
            else -> {
                println("Invalid input. Please enter again.")
                command = null
            }
        }
    } while (command == null)
}

fun main() {
    val hashTable = HashTable<String, String>(INITIAL_SIZE, SimpleHashFunction())
    hashTable.fileParser.stringToKey = { it }
    hashTable.fileParser.stringToValue = { it }
    val file = File(PATH_TO_TEXT_FILE)

    try {
        handleUserActions(hashTable, file)
    } catch (exception: FileNotFoundException) {
        println(exception.message)
    } catch (exception: IllegalStateException) {
        println("The file (\"$PATH_TO_TEXT_FILE\") from which the hash table is being filled is incorrect.")
    }
}
