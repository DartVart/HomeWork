
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