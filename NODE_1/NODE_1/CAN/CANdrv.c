#include "CANdrv.h"
#include "../MCP2515/MCP2515drv.h"


struct can_msg can_handle_msg(uint16_t id, uint8_t size, char msg[8]){
    struct can_msg msg;
    msg.id = id;
    msg.data_len = size;
    msg.data = msg;

    return msg;
}

void can_send_msg(struct can_msg* msg){

    uint8_t idLSB = (msg.id & 0x7) << 5;
    uint8_t idMSB = (msg.id & 0x7F8) >> 3;

    mcp2515_write(MCP_TXB0SIDH, idMSB);
    mcp2515_write(MCP_TXB0SIDL, idLSB);
    mcp2515_write(MCP_TXB0DLC, msg.data_len);

    for(uint8_t i = 0; i <= msg.data_len - 1; i++){
        mcp2515_write(MCP_TXBD0 + i, msg.data[i]);
    }


}

struct can_msg can_send_msg(){

    uint8_t idLSB = mcp2515_read() (msg.id & 0x7) << 5;
    uint8_t idMSB = (msg.id & 0x7F8) >> 3;

    mcp2515_write(MCP_TXB0SIDH, idMSB);
    mcp2515_write(MCP_TXB0SIDL, idLSB);
    mcp2515_write(MCP_TXB0DLC, msg.data_len);

    for(uint8_t i = 0; i <= msg.data_len - 1; i++){
        mcp2515_write(MCP_TXBD0 + i, msg.data[i]);
    }


}