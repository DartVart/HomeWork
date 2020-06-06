package homeworks.homework5.task1

import java.io.InputStream
import java.io.OutputStream

interface Serializable {
    fun serialize(outputStream: OutputStream)
    fun deserialize(inputStream: InputStream)
}
