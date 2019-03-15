from conans import ConanFile, CMake

class DriveFSConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch", "cppstd"

    # conan remote add public-conan https://api.bintray.com/conan/bincrafters/public-conan
    # conan remote add bisect https://api.bintray.com/conan/bisect/bisect
    # conan remote add ess-dmsc https://api.bintray.com/conan/ess-dmsc/conan \

    requires = (
            "boost/1.69.0@conan/stable",  "mongo-cxx-driver/3.3.0@bisect/stable",
            "cpprestsdk/2.10.10@bincrafters/stable","OpenSSL/1.0.2r@conan/stable",
            "jemalloc/5.0.1@ess-dmsc/stable"
    )

    generators = "cmake"
    default_options = {"OpenSSL:shared": False, "boost:shared": False, 
            "cpprestsdk:shared": False, "jemalloc:shared": False
    }
    build_policy = "missing"


    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin
        self.copy("*.so*", dst="lib", src="lib") # From lib to bin
        self.copy("*.a*", dst="lib", src="lib") # From lib to bin
        self.copy("*.h*", dst="include", src="include") # From lib to bin

    def build(self):
        if self.settings.os != "Windows":
            self.settings.compiler.libcxx = "libstdc++11"
        self.settings.cppstd=11
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

