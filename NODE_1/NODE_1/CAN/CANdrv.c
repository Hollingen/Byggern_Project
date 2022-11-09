#include "CANdrv.h"
#include "../MCP2515/MCP2515drv.h"


can_msg can_handle_msg(uint16_t id, uint8_t size, char msg[8]){
    can_msg msg;
    msg.id = id;
    msg.data_len = size;
    msg.data = msg;

    return msg;
}

void can_send_msg(can_msg* msg){

    uint8_t idLSB = (msg.id & 0x7) << 5;
    uint8_t idMSB = (msg.id & 0x7F8) >> 3;
    uint8_t buffer0stat;

    mcp2515_write(MCP_TXB0SIDH, idMSB);
    mcp2515_write(MCP_TXB0SIDL, idLSB);
    mcp2515_write(MCP_TXB0DLC, msg.data_len);

    // Checcking if the MCP is already requesting transmission in bffer 0
    if((mcp2515_read(MCP_TXB0CTRL) & 0x08) != 0x08){
        for(uint8_t i = 0; i <= msg.data_len - 1; i++){
            mcp2515_write(MCP_TXBD0 + i, msg.data[i]);
        }
        mcp2515_request_to_send(MCP_RTS_TX0);
    }
    

}

can_msg can_send_msg(BUFFER buffer){

    uint8_t idLSB = mcp2515_read() (msg.id & 0x7) << 5;
    uint8_t idMSB = (msg.id & 0x7F8) >> 3;

    mcp2515_write(MCP_TXB0SIDH + 16*buffer, idMSB);
    mcp2515_write(MCP_TXB0SIDL + 16*buffer, idLSB);
    mcp2515_write(MCP_TXB0DLC + 16*buffer, msg.data_len);

    for(uint8_t i = 0; i <= msg.data_len - 1; i++){
        mcp2515_write(MCP_TXBD0 + 16*buffer + i, msg.data[i]);
    }

}

can_msg can_recieve_msg(BUFFER buffer){
    can_msg msg;

    uint8_t idLSB = mcp2515_read(MCP_RXB0SIDL + 16*buffer);
    uint8_t idMSB = mcp2515_read(MCP_RXB0SIDH + 16*buffer);
    uint8_t msg_length = mcp2515_read(MCP_RXB0DLC + 16*buffer);
    msg.id = ((idLSB & 0b11100000) >> 5) | ((idMSB & 0b00011111) << 3);
    
    msg.data_len = msg_length;

    for(uint8_t i = 0; i <= msg.data_len - 1; i++){
        msg.data[i] = mcp2515_read(MCP_RXBD0 + 16*buffer + i, msg.data[i]);
    }

    return msg;

}

void interrupt_handler(){

    uint8_t status = mcp2515_read_status();

    if((status & stat_buff0_r) = stat_buff0_r){
        can_recieve(BUFFER0);
    }
    
    if((status & stat_buff1_r) != stat_buff1_r){
        can_recieve(BUFFER1);
    }

    if((status & stat_buff0_tx) = stat_buff0_tx){
        //transmission successfull
    }
    if((status & stat_buff1_tx) = stat_buff1_tx){
        //transmission successfull
    }
    if((status & stat_buff0_busy) = stat_buff0_busy){
        printf("BUFFER 0 is currently busy \n\r");
    }
    if((status & stat_buff1_busy) = stat_buff1_busy){
        printf("BUFFER 1 is currently busy \n\r");
    }
    

}

ISR(INT1_vector){
    interrupt_handler();
}