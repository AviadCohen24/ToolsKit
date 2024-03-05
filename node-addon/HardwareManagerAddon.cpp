#include <napi.h>
#include "HardwareManager.cpp"

Napi::String GPIOConfig(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    HardwareManager::GPIO_CONFIG();
    return Napi::String::New(env, "GPIO Configured");
}

Napi::String ExportGpio(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int pin = info[0].As<Napi::Number>().Int32Value();
    HardwareManager::exportGpio(pin);
    return Napi::String::New(env, "GPIO Exported");
}

Napi::String SetGpioDirection(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int pin = info[0].As<Napi::Number>().Int32Value();
    std::string direction = info[1].As<Napi::String>().Utf8Value();
    HardwareManager::setGpioDirection(pin, direction.c_str());
    return Napi::String::New(env, "GPIO Direction Set");
}

Napi::String WriteGpioValue(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int pin = info[0].As<Napi::Number>().Int32Value();
    int value = info[1].As<Napi::Number>().Int32Value();
    HardwareManager::writeGpioValue(pin, value);
    return Napi::String::New(env, "GPIO Value Written");
}

Napi::String WriteHeight(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    long height_data = info[0].As<Napi::Number>().Int64Value();
    HardwareManager::Write_Height(height_data);
    return Napi::String::New(env, "ARINC Height Written");
}

Napi::String WriteWoW(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    long WoW_data = info[0].As<Napi::Number>().Int64Value();
    HardwareManager::Write_WoW(WoW_data);
    return Napi::String::New(env, "ARINC WoW Written");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("gpioConfig", Napi::Function::New(env, GPIOConfig));
    exports.Set("exportGpio", Napi::Function::New(env, ExportGpio));
    exports.Set("setGpioDirection", Napi::Function::New(env, SetGpioDirection));
    exports.Set("writeGpioValue", Napi::Function::New(env, WriteGpioValue));
    exports.Set("writeHeight", Napi::Function::New(env, WriteHeight));
    exports.Set("writeWoW", Napi::Function::New(env, WriteWoW));
    return exports;
}

NODE_API_MODULE(HardwareManagerAddon, Init)
