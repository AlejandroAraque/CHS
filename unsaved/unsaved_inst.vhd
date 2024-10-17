	component unsaved is
		port (
			clk_50_in_clk                         : in    std_logic                     := 'X';             -- clk
			clk_50_2_in_clk                       : in    std_logic                     := 'X';             -- clk
			clk_50_3_in_clk                       : in    std_logic                     := 'X';             -- clk
			reset_bridge_in_reset_n               : in    std_logic                     := 'X';             -- reset_n
			sys_clk_out_clk                       : out   std_logic;                                        -- clk
			sdram_clk_out_clk                     : out   std_logic;                                        -- clk
			vga_clk_out_clk                       : out   std_logic;                                        -- clk
			mtl_clk_out_clk                       : out   std_logic;                                        -- clk
			audio_clk_out_clk                     : out   std_logic;                                        -- clk
			sdram_wire_addr                       : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba                         : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n                      : out   std_logic;                                        -- cas_n
			sdram_wire_cke                        : out   std_logic;                                        -- cke
			sdram_wire_cs_n                       : out   std_logic;                                        -- cs_n
			sdram_wire_dq                         : inout std_logic_vector(31 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm                        : out   std_logic_vector(3 downto 0);                     -- dqm
			sdram_wire_ras_n                      : out   std_logic;                                        -- ras_n
			sdram_wire_we_n                       : out   std_logic;                                        -- we_n
			flash_bridge_out_tcm_address_out      : out   std_logic_vector(22 downto 0);                    -- tcm_address_out
			flash_bridge_out_tcm_read_n_out       : out   std_logic_vector(0 downto 0);                     -- tcm_read_n_out
			flash_bridge_out_tcm_write_n_out      : out   std_logic_vector(0 downto 0);                     -- tcm_write_n_out
			flash_bridge_out_tcm_data_out         : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- tcm_data_out
			flash_bridge_out_tcm_chipselect_n_out : out   std_logic_vector(0 downto 0)                      -- tcm_chipselect_n_out
		);
	end component unsaved;

	u0 : component unsaved
		port map (
			clk_50_in_clk                         => CONNECTED_TO_clk_50_in_clk,                         --        clk_50_in.clk
			clk_50_2_in_clk                       => CONNECTED_TO_clk_50_2_in_clk,                       --      clk_50_2_in.clk
			clk_50_3_in_clk                       => CONNECTED_TO_clk_50_3_in_clk,                       --      clk_50_3_in.clk
			reset_bridge_in_reset_n               => CONNECTED_TO_reset_bridge_in_reset_n,               --  reset_bridge_in.reset_n
			sys_clk_out_clk                       => CONNECTED_TO_sys_clk_out_clk,                       --      sys_clk_out.clk
			sdram_clk_out_clk                     => CONNECTED_TO_sdram_clk_out_clk,                     --    sdram_clk_out.clk
			vga_clk_out_clk                       => CONNECTED_TO_vga_clk_out_clk,                       --      vga_clk_out.clk
			mtl_clk_out_clk                       => CONNECTED_TO_mtl_clk_out_clk,                       --      mtl_clk_out.clk
			audio_clk_out_clk                     => CONNECTED_TO_audio_clk_out_clk,                     --    audio_clk_out.clk
			sdram_wire_addr                       => CONNECTED_TO_sdram_wire_addr,                       --       sdram_wire.addr
			sdram_wire_ba                         => CONNECTED_TO_sdram_wire_ba,                         --                 .ba
			sdram_wire_cas_n                      => CONNECTED_TO_sdram_wire_cas_n,                      --                 .cas_n
			sdram_wire_cke                        => CONNECTED_TO_sdram_wire_cke,                        --                 .cke
			sdram_wire_cs_n                       => CONNECTED_TO_sdram_wire_cs_n,                       --                 .cs_n
			sdram_wire_dq                         => CONNECTED_TO_sdram_wire_dq,                         --                 .dq
			sdram_wire_dqm                        => CONNECTED_TO_sdram_wire_dqm,                        --                 .dqm
			sdram_wire_ras_n                      => CONNECTED_TO_sdram_wire_ras_n,                      --                 .ras_n
			sdram_wire_we_n                       => CONNECTED_TO_sdram_wire_we_n,                       --                 .we_n
			flash_bridge_out_tcm_address_out      => CONNECTED_TO_flash_bridge_out_tcm_address_out,      -- flash_bridge_out.tcm_address_out
			flash_bridge_out_tcm_read_n_out       => CONNECTED_TO_flash_bridge_out_tcm_read_n_out,       --                 .tcm_read_n_out
			flash_bridge_out_tcm_write_n_out      => CONNECTED_TO_flash_bridge_out_tcm_write_n_out,      --                 .tcm_write_n_out
			flash_bridge_out_tcm_data_out         => CONNECTED_TO_flash_bridge_out_tcm_data_out,         --                 .tcm_data_out
			flash_bridge_out_tcm_chipselect_n_out => CONNECTED_TO_flash_bridge_out_tcm_chipselect_n_out  --                 .tcm_chipselect_n_out
		);

