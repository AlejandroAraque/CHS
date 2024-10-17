
module nios_system (
	audio_config_external_interface_SDAT,
	audio_config_external_interface_SCLK,
	audio_external_interface_ADCDAT,
	audio_external_interface_ADCLRCK,
	audio_external_interface_BCLK,
	audio_external_interface_DACDAT,
	audio_external_interface_DACLRCK,
	char_lcd_external_interface_DATA,
	char_lcd_external_interface_ON,
	char_lcd_external_interface_BLON,
	char_lcd_external_interface_EN,
	char_lcd_external_interface_RS,
	char_lcd_external_interface_RW,
	clk_50_2_in_clk,
	clk_50_3_in_clk,
	clk_50_in_clk,
	flash_bridge_out_tcm_address_out,
	flash_bridge_out_tcm_read_n_out,
	flash_bridge_out_tcm_write_n_out,
	flash_bridge_out_tcm_data_out,
	flash_bridge_out_tcm_chipselect_n_out,
	green_leds_external_interface_export,
	hex3_hex0_external_interface_HEX0,
	hex3_hex0_external_interface_HEX1,
	hex3_hex0_external_interface_HEX2,
	hex3_hex0_external_interface_HEX3,
	mtl_clk_out_clk,
	mtl_controller_external_interface_CLK,
	mtl_controller_external_interface_HS,
	mtl_controller_external_interface_VS,
	mtl_controller_external_interface_DATA_EN,
	mtl_controller_external_interface_R,
	mtl_controller_external_interface_G,
	mtl_controller_external_interface_B,
	parallel_port_0_external_interface_HEX4,
	parallel_port_0_external_interface_HEX5,
	parallel_port_0_external_interface_HEX6,
	parallel_port_0_external_interface_HEX7,
	ps2_key_external_interface_CLK,
	ps2_key_external_interface_DAT,
	ps2_mouse_external_interface_CLK,
	ps2_mouse_external_interface_DAT,
	pushbuttons_external_interface_export,
	red_leds_external_interface_export,
	reset_bridge_in_reset_n,
	sd_card_conduit_end_b_SD_cmd,
	sd_card_conduit_end_b_SD_dat,
	sd_card_conduit_end_b_SD_dat3,
	sd_card_conduit_end_o_SD_clock,
	sdram_clk_out_clk,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	serial_port_external_interface_RXD,
	serial_port_external_interface_TXD,
	sram_external_interface_DQ,
	sram_external_interface_ADDR,
	sram_external_interface_LB_N,
	sram_external_interface_UB_N,
	sram_external_interface_CE_N,
	sram_external_interface_OE_N,
	sram_external_interface_WE_N,
	switches_external_interface_export,
	sys_clk_out_clk,
	vga_clk_out_clk);	

	inout		audio_config_external_interface_SDAT;
	output		audio_config_external_interface_SCLK;
	input		audio_external_interface_ADCDAT;
	input		audio_external_interface_ADCLRCK;
	input		audio_external_interface_BCLK;
	output		audio_external_interface_DACDAT;
	input		audio_external_interface_DACLRCK;
	inout	[7:0]	char_lcd_external_interface_DATA;
	output		char_lcd_external_interface_ON;
	output		char_lcd_external_interface_BLON;
	output		char_lcd_external_interface_EN;
	output		char_lcd_external_interface_RS;
	output		char_lcd_external_interface_RW;
	input		clk_50_2_in_clk;
	input		clk_50_3_in_clk;
	input		clk_50_in_clk;
	output	[22:0]	flash_bridge_out_tcm_address_out;
	output	[0:0]	flash_bridge_out_tcm_read_n_out;
	output	[0:0]	flash_bridge_out_tcm_write_n_out;
	inout	[7:0]	flash_bridge_out_tcm_data_out;
	output	[0:0]	flash_bridge_out_tcm_chipselect_n_out;
	output	[8:0]	green_leds_external_interface_export;
	output	[6:0]	hex3_hex0_external_interface_HEX0;
	output	[6:0]	hex3_hex0_external_interface_HEX1;
	output	[6:0]	hex3_hex0_external_interface_HEX2;
	output	[6:0]	hex3_hex0_external_interface_HEX3;
	output		mtl_clk_out_clk;
	output		mtl_controller_external_interface_CLK;
	output		mtl_controller_external_interface_HS;
	output		mtl_controller_external_interface_VS;
	output		mtl_controller_external_interface_DATA_EN;
	output	[7:0]	mtl_controller_external_interface_R;
	output	[7:0]	mtl_controller_external_interface_G;
	output	[7:0]	mtl_controller_external_interface_B;
	output	[6:0]	parallel_port_0_external_interface_HEX4;
	output	[6:0]	parallel_port_0_external_interface_HEX5;
	output	[6:0]	parallel_port_0_external_interface_HEX6;
	output	[6:0]	parallel_port_0_external_interface_HEX7;
	inout		ps2_key_external_interface_CLK;
	inout		ps2_key_external_interface_DAT;
	inout		ps2_mouse_external_interface_CLK;
	inout		ps2_mouse_external_interface_DAT;
	input	[3:0]	pushbuttons_external_interface_export;
	output	[17:0]	red_leds_external_interface_export;
	input		reset_bridge_in_reset_n;
	inout		sd_card_conduit_end_b_SD_cmd;
	inout		sd_card_conduit_end_b_SD_dat;
	inout		sd_card_conduit_end_b_SD_dat3;
	output		sd_card_conduit_end_o_SD_clock;
	output		sdram_clk_out_clk;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[31:0]	sdram_wire_dq;
	output	[3:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	input		serial_port_external_interface_RXD;
	output		serial_port_external_interface_TXD;
	inout	[15:0]	sram_external_interface_DQ;
	output	[19:0]	sram_external_interface_ADDR;
	output		sram_external_interface_LB_N;
	output		sram_external_interface_UB_N;
	output		sram_external_interface_CE_N;
	output		sram_external_interface_OE_N;
	output		sram_external_interface_WE_N;
	input	[17:0]	switches_external_interface_export;
	output		sys_clk_out_clk;
	output		vga_clk_out_clk;
endmodule
