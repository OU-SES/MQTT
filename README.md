# OU-SES

# MQTT Message DLL

This project provides a Dynamic-Link Library (DLL) for generating and interpreting MQTT messages in C++. It can be built using **Visual Studio** or **CMake** on a Windows 64-bit system.

## 📁 Project Structure

All source files are located in a single folder:

- `DataConvertor.cpp`
- `MQTTMessageFactory.cpp`
- `PacketGenerator.cpp`
- `PacketInterpreter.cpp`
- `dllmain.cpp`
- `pch.cpp` *(optional precompiled header source)*

## 🛠️ Prerequisites

- Windows 64-bit system
- C++ compiler (MSVC via Visual Studio or `cl.exe`)
- [CMake](https://cmake.org/download/) (if not using Visual Studio directly)

---

## 💻 Option 1: Build Using Visual Studio

**Create a New Visual Studio DLL Project Manually**
   - Open Visual Studio and create a new **C++ Dynamic-Link Library (DLL)** project
   - Add all `.cpp` and `.h` files to the project
   - Set the configuration to `x64` and `Release`
   - Build the project to generate the DLL

---

## ⚙️ Option 2: Build Using CMake

1. **Create a `CMakeLists.txt` File**  
   Add the following content:

   ```cmake
   cmake_minimum_required(VERSION 3.10)
    project(MQTT_DLL LANGUAGES CXX)
    
    # Optional: List all header files for clarity
    set(HEADER_FILES
        AssignedClientIdentifier.h
        ConnackFixedHeader.h
        ConnackVariableHeader.h
        ConnectFixedHeader.h
        ConnectPayload.h
        ConnectVariableHeader.h
        DataConvertor.h
        FixedHeader.h
        FourByteInteger.h
        MQTTConnackMessage.h
        MQTTConnectMessage.h
        MQTTControlPacketList.h
        MQTTMessage.h
        MQTTMessageFactory.h
        MQTTPubRecMessage.h
        MQTTPubRelMessage.h
        MQTTPubackMessage.h
        MQTTPubcompMessage.h
        MQTTPublishMessage.h
        MQTTSubackMessage.h
        MQTTSubscribeMessage.h
        PacketGenerator.h
        PacketInterpreter.h
        PayloadFormatIndicator.h
        Property.h
        PropertyPacketGenerator.h
        PubRecFixedHeader.h
        PubRecVariableHeader.h
        PubackFixedHeader.h
        PubackVariableHeader.h
        PubcompFixedHeader.h
        PubcompVariableHeader.h
        PublishFixedHeader.h
        PublishVariableHeader.h
        PubrelFixedHeader.h
        PubrelVariableHeader.h
        ServerReference.h
        SessionExpiryInterval.h
        SubackFixedHeader.h
        SubackPayload.h
        SubackVariableHeader.h
        SubscribeFixedHeader.h
        SubscribePayload.h
        SubscribeVariableHeader.h
        SubscriptionIdentifiersAvailable.h
        TwoByteInteger.h
        UTF8String.h
        UserProperty.h
        VariableByteInteger.h
        VariableHeader.h
        framework.h
        pch.h             # Only if used
    )
    
    # List all source files
    set(SOURCE_FILES
        DataConvertor.cpp
        MQTTMessageFactory.cpp
        PacketGenerator.cpp
        PacketInterpreter.cpp
        dllmain.cpp
        pch.cpp           # Only if used
    )
    
    # Create DLL target
    add_library(MQTT_DLL SHARED
        ${HEADER_FILES}
        ${SOURCE_FILES}
    )
    
    # Output directory for DLL
    set_target_properties(MQTT_DLL PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
    
    # Export all symbols (Windows)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    
    # Add include paths
    target_include_directories(MQTT_DLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
2. **Generate Build Files**

   Open a terminal in the project directory and run:
   
      ```sh
      mkdir build
      cd build
      cmake .. -G "Visual Studio 16 2019" -A x64
      ```
   Replace the generator string with your Visual Studio version if different.
3. **Build the DLL**  
   Run the following command inside the `build` folder:

       cmake --build . --config Release

   After building, you will find the following files in `./build/Release/`:

   - MQTT_DLL.dll – The compiled dynamic link library  
   - MQTT_DLL.lib – Import library for linking  
   - MQTT_DLL.pdb – Debug symbols (optional)

   This confirms that CMake correctly built the DLL without needing a `.sln` file.

## Usage

After building, you can:

- Use `MQTTMessageFactory` or `PacketGenerator` to generate MQTT messages.
- Use `PacketInterpreter` to interpret MQTT packets.

Ensure the `.dll` and header files are included or distributed properly in the consuming application.

## Notes

- If you are not using precompiled headers (`pch.cpp`, `pch.h`), remove them from the `CMakeLists.txt`.
- You can use `__declspec(dllexport)` or enable `CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS` in your CMake file to export symbols automatically.
