
module unsaved (
	clk_50_in_clk,
	clk_50_2_in_clk,
	clk_50_3_in_clk,
	reset_bridge_in_reset_n,
	sys_clk_out_clk,
	sdram_clk_out_clk,
	vga_clk_out_clk,
	mtl_clk_out_clk,
	audio_clk_out_clk,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	flash_bridge_out_tcm_address_out,
	flash_bridge_out_tcm_read_n_out,
	flash_bridge_out_tcm_write_n_out,
	flash_bridge_out_tcm_data_out,
	flash_bridge_out_tcm_chipselect_n_out);	

	input		clk_50_in_clk;
	input		clk_50_2_in_clk;
	input		clk_50_3_in_clk;
	input		reset_bridge_in_reset_n;
	output		sys_clk_out_clk;
	output		sdram_clk_out_clk;
	output		vga_clk_out_clk;
	output		mtl_clk_out_clk;
	output		audio_clk_out_clk;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[31:0]	sdram_wire_dq;
	output	[3:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output	[22:0]	flash_bridge_out_tcm_address_out;
	output	[0:0]	flash_bridge_out_tcm_read_n_out;
	output	[0:0]	flash_bridge_out_tcm_write_n_out;
	inout	[7:0]	flash_bridge_out_tcm_data_out;
	output	[0:0]	flash_bridge_out_tcm_chipselect_n_out;
endmodule
