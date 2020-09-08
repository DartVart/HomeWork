plugins {
    kotlin("jvm") version "1.3.71"
    id("io.gitlab.arturbosch.detekt") version "1.6.0"
    application
    id("org.openjfx.javafxplugin") version "0.0.8"
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
    jcenter()
}

val ktorVersion = "1.3.2"

dependencies {
    implementation(kotlin("stdlib-jdk8"))
    implementation("org.junit.jupiter:junit-jupiter-api:5.6.0")
    implementation("org.junit.jupiter:junit-jupiter-engine:5.6.0")
    implementation("org.jetbrains.kotlinx:kotlinx-coroutines-core:1.3.5")
    implementation("no.tornado:tornadofx:1.7.20")
    detektPlugins("io.gitlab.arturbosch.detekt:detekt-formatting:1.6.0")
    implementation("org.openjfx:javafx-base:11.0.2")
    implementation("org.openjfx:javafx:11.0.2")
    implementation("org.openjfx:javafx-controls:11.0.2")
    implementation("org.openjfx:javafx-maven-plugin:0.0.4")
    implementation("io.ktor:ktor-client-websockets:$ktorVersion")
    implementation("io.ktor:ktor-client-cio:$ktorVersion")
    implementation("io.ktor:ktor-client-js:$ktorVersion")
    implementation("io.ktor:ktor-client-okhttp:$ktorVersion")
    implementation("io.ktor:ktor-websockets:$ktorVersion")
    implementation("org.jetbrains.kotlinx:kotlinx-serialization-runtime-native:0.9.1")
    implementation("org.jetbrains.kotlin:kotlin-reflect:1.3.70")
    implementation("org.jetbrains.kotlinx:kotlinx-coroutines-core:1.3.5")
    compile("io.ktor:ktor-server-netty:1.3.2")
    compile("io.ktor:ktor-server-core:1.3.2")
}

javafx {
    modules("javafx.controls")
}

detekt {
    failFast = true // fail build on any finding
    buildUponDefaultConfig = true // preconfigure defaults
}

tasks {
    compileKotlin {
        kotlinOptions.jvmTarget = "1.8"
    }
    compileTestKotlin {
        kotlinOptions.jvmTarget = "1.8"
    }
    test {
        useJUnitPlatform()
    }
}