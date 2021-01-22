#include <ipmid/api.h>
#include <ipmid/api.hpp>
#include <ipmid/utils.hpp>
#include <ipmid/api-types.hpp>
#include <iostream>
#include <variant>
#include <sdbusplus/bus.hpp>
#include <ipmid/handler.hpp>

int get_dbus();
void set_dbus();
// Declares register function with attribute "constructor".
void register_netfn_oem_functions() __attribute__((constructor));


// busctl get-property xyz.openbmc_project.Hwmon-4134958689.Hwmon1 
//               /xyz/openbmc_project/sensors/voltage/ADC8 
//               xyz.openbmc_project.Sensor.Value Value
static constexpr auto vsensorserv =  "xyz.openbmc_project.Hwmon-4134958689.Hwmon1";
static constexpr auto vsensorObj = "/xyz/openbmc_project/sensors/voltage/ADC8";
static constexpr auto vsensorIntf = "xyz.openbmc_project.Sensor.Value";
static constexpr auto vsensorProp = "Value";

int get_dbus()
{

    std::cout << __FUNCTION__ << " entered! " << std::endl;
    using Value = std::variant<int32_t>;
    Value value;
    auto sdbus = sdbusplus::bus::new_default();
    auto sdmethod = sdbus.new_method_call(\
        vsensorserv, \
        vsensorObj, \
        "org.freedesktop.DBus.Properties", \
        "Get");
    sdmethod.append(vsensorIntf, vsensorProp);
    auto reply = sdbus.call(sdmethod);
    reply.read(value);
    auto arv_result = std::get<int32_t>(value);
    std::cout << "arv_result: " << arv_result << "\n";
    std::cout << "arv_result_str: " << std::to_string(arv_result) << "\n";

    std::cout << __FUNCTION__ << " exit! " << std::endl;
    return arv_result; 
}

void set_dbus()
{
    using Value = std::variant<int32_t>;
    Value value = 28;
    auto sdbus = sdbusplus::bus::new_default();
    auto sdmethod = sdbus.new_method_call("xyz.openbmc_project.hello_dbus", "/xyz/openbmc_project/hello_dbus/custom", "org.freedesktop.DBus.Properties", "Set");
    sdmethod.append("xyz.openbmc_project.hello_dbus.custom.Example", "OemInt", value);
    auto reply = sdbus.call(sdmethod);
}

// Callback function for handling Oem command 0xBA.
ipmi_ret_t ipmi_my_handler1(ipmi_netfn_t netfn, ipmi_cmd_t cmd,
                            ipmi_request_t request, ipmi_response_t response,
                            ipmi_data_len_t data_len, ipmi_context_t context)
{
    std::cout << __FUNCTION__ << " entered! " << std::endl;

    ipmi_ret_t rc = IPMI_CC_OK;
    uint8_t rspa[] = {0xFF, 0x00, 0xAA, 0x55, 0x32, 0xBA};

    std::cout << "rspa static cast " ;
    for(int arvi = 0; arvi<=5; arvi++) {
      std::cout << static_cast<int>(rspa[arvi]) <<  " ";  }
    std::cout << std::endl;
    // cout->print result() - rsp static cast 55 aa 0 ff 32 be

    uint8_t rsp = get_dbus();
    std::cout << "=== aaarrv get dbus === " << static_cast<int>(rsp) << std::endl;
    //memcpy(response, &rsp, 6);
    memcpy(response, &rsp, 1);
    //*data_len = 4;
    *data_len = 0;

    return rc;
}

// Callback function for handling OEM command 0xBE.
ipmi_ret_t ipmi_my_handler2(ipmi_netfn_t netfn, ipmi_cmd_t cmd,
                            ipmi_request_t request, ipmi_response_t response,
                            ipmi_data_len_t data_len, ipmi_context_t context)
{
    std::cout << __FUNCTION__ << " entered! " << std::endl;

    ipmi_ret_t rc = IPMI_CC_OK;
    uint8_t rsp[6] = {0x55, 0xAA, 0x00, 0xFF, 0x32, 0xBE};

    std::cout << "rsp std::hex  " ;
    for (auto& rsps : rsp){
        std::cout << std::hex << std::stoi(std::to_string(rsps),NULL,16) << " " ;
    }
    std::cout << std::endl;
    // cout->print result() - rsp std::hex  85 170 0 255 50 190

    std::cout << "rsp to_string " ;
    for(int arvi = 0; arvi<=5; arvi++) {
      std::cout << std::to_string(rsp[arvi]) <<  " ";  }
    std::cout << std::endl;
    // cout->print result() - rsp to_string 85 170 0 255 50 190

    std::cout << "rsp static cast " ;
    for(int arvi = 0; arvi<=5; arvi++) {
      std::cout << static_cast<int>(rsp[arvi]) <<  " ";  }
    std::cout << std::endl;
    // cout->print result() - rsp static cast 55 aa 0 ff 32 be

    memcpy(response, &rsp, 6);
        std::cout << "response - " << response << std::endl;
    unsigned char arvrsp[10];

    std::cout << "response - static_cast ";
    memcpy(&arvrsp, response, 6);
    for(int arvi =0 ; arvi<=5 ; arvi++) {
        std::cout << static_cast<int>(arvrsp[arvi]) << " "; }
    std::cout << std::endl;


	// set_dbus();
    *data_len = 6;

    return rc;
}

// Register function
void register_netfn_oem_functions()
{
    std::cout << "Registering OEM command handlers" << std::endl;
    ipmi_register_callback(NETFUN_OEM, 0xBA, NULL, ipmi_my_handler1, PRIVILEGE_USER);
    ipmi_register_callback(NETFUN_OEM, 0xBE, NULL, ipmi_my_handler2, PRIVILEGE_USER);

    return;
}