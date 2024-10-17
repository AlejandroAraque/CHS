	nios_system u0 (
		.audio_config_external_interface_SDAT      (<connected-to-audio_config_external_interface_SDAT>),      //    audio_config_external_interface.SDAT
		.audio_config_external_interface_SCLK      (<connected-to-audio_config_external_interface_SCLK>),      //                                   .SCLK
		.audio_external_interface_ADCDAT           (<connected-to-audio_external_interface_ADCDAT>),           //           audio_external_interface.ADCDAT
		.audio_external_interface_ADCLRCK          (<connected-to-audio_external_interface_ADCLRCK>),          //                                   .ADCLRCK
		.audio_external_interface_BCLK             (<connected-to-audio_external_interface_BCLK>),             //                                   .BCLK
		.audio_external_interface_DACDAT           (<connected-to-audio_external_interface_DACDAT>),           //                                   .DACDAT
		.audio_external_interface_DACLRCK          (<connected-to-audio_external_interface_DACLRCK>),          //                                   .DACLRCK
		.char_lcd_external_interface_DATA          (<connected-to-char_lcd_external_interface_DATA>),          //        char_lcd_external_interface.DATA
		.char_lcd_external_interface_ON            (<connected-to-char_lcd_external_interface_ON>),            //                                   .ON
		.char_lcd_external_interface_BLON          (<connected-to-char_lcd_external_interface_BLON>),          //                                   .BLON
		.char_lcd_external_interface_EN            (<connected-to-char_lcd_external_interface_EN>),            //                                   .EN
		.char_lcd_external_interface_RS            (<connected-to-char_lcd_external_interface_RS>),            //                                   .RS
		.char_lcd_external_interface_RW            (<connected-to-char_lcd_external_interface_RW>),            //                                   .RW
		.clk_50_2_in_clk                           (<connected-to-clk_50_2_in_clk>),                           //                        clk_50_2_in.clk
		.clk_50_3_in_clk                           (<connected-to-clk_50_3_in_clk>),                           //                        clk_50_3_in.clk
		.clk_50_in_clk                             (<connected-to-clk_50_in_clk>),                             //                          clk_50_in.clk
		.flash_bridge_out_tcm_address_out          (<connected-to-flash_bridge_out_tcm_address_out>),          //                   flash_bridge_out.tcm_address_out
		.flash_bridge_out_tcm_read_n_out           (<connected-to-flash_bridge_out_tcm_read_n_out>),           //                                   .tcm_read_n_out
		.flash_bridge_out_tcm_write_n_out          (<connected-to-flash_bridge_out_tcm_write_n_out>),          //                                   .tcm_write_n_out
		.flash_bridge_out_tcm_data_out             (<connected-to-flash_bridge_out_tcm_data_out>),             //                                   .tcm_data_out
		.flash_bridge_out_tcm_chipselect_n_out     (<connected-to-flash_bridge_out_tcm_chipselect_n_out>),     //                                   .tcm_chipselect_n_out
		.green_leds_external_interface_export      (<connected-to-green_leds_external_interface_export>),      //      green_leds_external_interface.export
		.hex3_hex0_external_interface_HEX0         (<connected-to-hex3_hex0_external_interface_HEX0>),         //       hex3_hex0_external_interface.HEX0
		.hex3_hex0_external_interface_HEX1         (<connected-to-hex3_hex0_external_interface_HEX1>),         //                                   .HEX1
		.hex3_hex0_external_interface_HEX2         (<connected-to-hex3_hex0_external_interface_HEX2>),         //                                   .HEX2
		.hex3_hex0_external_interface_HEX3         (<connected-to-hex3_hex0_external_interface_HEX3>),         //                                   .HEX3
		.mtl_clk_out_clk                           (<connected-to-mtl_clk_out_clk>),                           //                        mtl_clk_out.clk
		.mtl_controller_external_interface_CLK     (<connected-to-mtl_controller_external_interface_CLK>),     //  mtl_controller_external_interface.CLK
		.mtl_controller_external_interface_HS      (<connected-to-mtl_controller_external_interface_HS>),      //                                   .HS
		.mtl_controller_external_interface_VS      (<connected-to-mtl_controller_external_interface_VS>),      //                                   .VS
		.mtl_controller_external_interface_DATA_EN (<connected-to-mtl_controller_external_interface_DATA_EN>), //                                   .DATA_EN
		.mtl_controller_external_interface_R       (<connected-to-mtl_controller_external_interface_R>),       //                                   .R
		.mtl_controller_external_interface_G       (<connected-to-mtl_controller_external_interface_G>),       //                                   .G
		.mtl_controller_external_interface_B       (<connected-to-mtl_controller_external_interface_B>),       //                                   .B
		.parallel_port_0_external_interface_HEX4   (<connected-to-parallel_port_0_external_interface_HEX4>),   // parallel_port_0_external_interface.HEX4
		.parallel_port_0_external_interface_HEX5   (<connected-to-parallel_port_0_external_interface_HEX5>),   //                                   .HEX5
		.parallel_port_0_external_interface_HEX6   (<connected-to-parallel_port_0_external_interface_HEX6>),   //                                   .HEX6
		.parallel_port_0_external_interface_HEX7   (<connected-to-parallel_port_0_external_interface_HEX7>),   //                                   .HEX7
		.ps2_key_external_interface_CLK            (<connected-to-ps2_key_external_interface_CLK>),            //         ps2_key_external_interface.CLK
		.ps2_key_external_interface_DAT            (<connected-to-ps2_key_external_interface_DAT>),            //                                   .DAT
		.ps2_mouse_external_interface_CLK          (<connected-to-ps2_mouse_external_interface_CLK>),          //       ps2_mouse_external_interface.CLK
		.ps2_mouse_external_interface_DAT          (<connected-to-ps2_mouse_external_interface_DAT>),          //                                   .DAT
		.pushbuttons_external_interface_export     (<connected-to-pushbuttons_external_interface_export>),     //     pushbuttons_external_interface.export
		.red_leds_external_interface_export        (<connected-to-red_leds_external_interface_export>),        //        red_leds_external_interface.export
		.reset_bridge_in_reset_n                   (<connected-to-reset_bridge_in_reset_n>),                   //                    reset_bridge_in.reset_n
		.sd_card_conduit_end_b_SD_cmd              (<connected-to-sd_card_conduit_end_b_SD_cmd>),              //                sd_card_conduit_end.b_SD_cmd
		.sd_card_conduit_end_b_SD_dat              (<connected-to-sd_card_conduit_end_b_SD_dat>),              //                                   .b_SD_dat
		.sd_card_conduit_end_b_SD_dat3             (<connected-to-sd_card_conduit_end_b_SD_dat3>),             //                                   .b_SD_dat3
		.sd_card_conduit_end_o_SD_clock            (<connected-to-sd_card_conduit_end_o_SD_clock>),            //                                   .o_SD_clock
		.sdram_clk_out_clk                         (<connected-to-sdram_clk_out_clk>),                         //                      sdram_clk_out.clk
		.sdram_wire_addr                           (<connected-to-sdram_wire_addr>),                           //                         sdram_wire.addr
		.sdram_wire_ba                             (<connected-to-sdram_wire_ba>),                             //                                   .ba
		.sdram_wire_cas_n                          (<connected-to-sdram_wire_cas_n>),                          //                                   .cas_n
		.sdram_wire_cke                            (<connected-to-sdram_wire_cke>),                            //                                   .cke
		.sdram_wire_cs_n                           (<connected-to-sdram_wire_cs_n>),                           //                                   .cs_n
		.sdram_wire_dq                             (<connected-to-sdram_wire_dq>),                             //                                   .dq
		.sdram_wire_dqm                            (<connected-to-sdram_wire_dqm>),                            //                                   .dqm
		.sdram_wire_ras_n                          (<connected-to-sdram_wire_ras_n>),                          //                                   .ras_n
		.sdram_wire_we_n                           (<connected-to-sdram_wire_we_n>),                           //                                   .we_n
		.serial_port_external_interface_RXD        (<connected-to-serial_port_external_interface_RXD>),        //     serial_port_external_interface.RXD
		.serial_port_external_interface_TXD        (<connected-to-serial_port_external_interface_TXD>),        //                                   .TXD
		.sram_external_interface_DQ                (<connected-to-sram_external_interface_DQ>),                //            sram_external_interface.DQ
		.sram_external_interface_ADDR              (<connected-to-sram_external_interface_ADDR>),              //                                   .ADDR
		.sram_external_interface_LB_N              (<connected-to-sram_external_interface_LB_N>),              //                                   .LB_N
		.sram_external_interface_UB_N              (<connected-to-sram_external_interface_UB_N>),              //                                   .UB_N
		.sram_external_interface_CE_N              (<connected-to-sram_external_interface_CE_N>),              //                                   .CE_N
		.sram_external_interface_OE_N              (<connected-to-sram_external_interface_OE_N>),              //                                   .OE_N
		.sram_external_interface_WE_N              (<connected-to-sram_external_interface_WE_N>),              //                                   .WE_N
		.switches_external_interface_export        (<connected-to-switches_external_interface_export>),        //        switches_external_interface.export
		.sys_clk_out_clk                           (<connected-to-sys_clk_out_clk>),                           //                        sys_clk_out.clk
		.vga_clk_out_clk                           (<connected-to-vga_clk_out_clk>)                            //                        vga_clk_out.clk
	);

