#include "CANdrv.h"
#include "../MCP2515/MCP2515drv.h"


can_msg can_handle_msg(uint16_t id, uint8_t size, char msg_data[8]){
    can_msg msg;
    msg.id = id;
    msg.data_len = size;
	//printf("her\n\r");
	for(uint8_t i = 0; i < size; i++){
		msg.data[i] = msg_data[i];
		//printf("array: %d\n\r",msg_data[i]);
		
	}
	//printf("kis %d og %d\n\r", msg.data[0], msg.data[1]);
    return msg;
	
}

void can_send_msg(can_msg* msg, BUFFER buffer){

    uint8_t idLSB = (msg->id & 0x7) << 5;
    uint8_t idMSB = (msg->id & 0x7F8) >> 3;
    //uint8_t buffer0stat;

    mcp2515_write(MCP_TXB0SIDH + 16*buffer, idMSB);
    mcp2515_write(MCP_TXB0SIDL + 16*buffer, idLSB);
    mcp2515_write(MCP_TXB0DLC + 16*buffer, msg->data_len);
	//printf("length: %d\n\r", msg->data_len);

    // Checking if the MCP is already requesting transmission in buffer 0
	uint8_t value;
	mcp2515_read(MCP_TXB0CTRL, &value);
    if((value & 0x08) != 0x08){
        for(uint8_t i = 0; i < msg->data_len; i++){
            mcp2515_write(MCP_TXBD0 + 16*buffer + i, msg->data[i]);
			//printf("data %d\n\r", msg->data[i]);
			
        }
        mcp2515_request_to_send(MCP_RTS_TX0 + buffer);
    }
    

}


can_msg can_recieve_msg(BUFFER buffer){
	//printf("her");
    can_msg msg;
	//printf("buffer%d\n\r", buffer);
    uint8_t idLSB;
	mcp2515_read(MCP_RXB0SIDL + 16*buffer, &idLSB);
    uint8_t idMSB;
	mcp2515_read(MCP_RXB0SIDH + 16*buffer, &idMSB);
    uint8_t msg_length;
	mcp2515_read(MCP_RXB0DLC + 16*buffer, &msg_length);
    msg.id = ((idLSB & 0b11100000) >> 5) | ((idMSB & 0b00011111) << 3);
    
    msg.data_len = msg_length;
	
    for(uint8_t i = 0; i < msg.data_len; i++){
		uint8_t data_tmp;
		mcp2515_read(MCP_RXBD0 + 16*buffer + i, &data_tmp);
        msg.data[i] = data_tmp;
    }

    return msg;

}

void interrupt_handler(){

    uint8_t status = mcp2515_read_status();
    can_msg msg;

    if((status & stat_buff0_r) == stat_buff0_r){
        msg = can_recieve_msg(BUFFER0);
        printf("BUFFER0: ID = %d, MESSAGE = ", msg.id);
        for (uint8_t i = 0; i < msg.data_len; i++){
            printf("%d", msg.data[i]);
        }
        printf("\n\r");
    }
    
    if((status & stat_buff1_r) == stat_buff1_r){
        msg = can_recieve_msg(BUFFER1);
        printf("BUFFER1: ID = %d, MESSAGE = ", msg.id);
        for (uint8_t i = 0; i < msg.data_len; i++){
            printf("%d", msg.data[i]);
        }
        printf("\n\r");
    }

    if((status & stat_buff0_tx) == stat_buff0_tx){
        //transmission successfull
		printf("yo\n\r");
    }
    if((status & stat_buff1_tx) == stat_buff1_tx){
        //transmission successfull
    }
    if((status & stat_buff0_busy) == stat_buff0_busy){
        printf("BUFFER 0 is currently busy \n\r");
    }
    if((status & stat_buff1_busy) == stat_buff1_busy){
        printf("BUFFER 1 is currently busy \n\r");
    }
   //mcp2515_bit_modify(MCP_CANINTF, 0xFF, 0x00); 

}

/*ISR(INT1_vector){
    interrupt_handler();
	printf("nei\n\r");
}*/