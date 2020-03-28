plugins {
    kotlin("jvm") version "1.3.61"
    id("io.gitlab.arturbosch.detekt") version "1.6.0"
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
    jcenter {
        content {
            includeGroup("org.jetbrains.kotlinx")
        }
    }
}

dependencies {
    implementation(kotlin("stdlib-jdk8"))
    implementation("org.junit.jupiter:junit-jupiter-api:5.6.0")
    implementation("org.junit.jupiter:junit-jupiter-engine:5.6.0")
    detektPlugins("io.gitlab.arturbosch.detekt:detekt-formatting:1.6.0")
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