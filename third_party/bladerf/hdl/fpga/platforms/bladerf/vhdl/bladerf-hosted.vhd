-- Copyright (c) 2013 Nuand LLC
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.

library ieee ;
    use ieee.std_logic_1164.all ;
    use ieee.numeric_std.all ;
    use ieee.math_real.all ;
    use ieee.math_complex.all ;

architecture hosted_bladerf of bladerf is

    attribute noprune   : boolean ;
    attribute keep      : boolean ;

    component nios_system is
      port (
        clk_clk             : in  std_logic := 'X'; -- clk
        reset_reset_n       : in  std_logic := 'X'; -- reset_n
        dac_MISO            : in  std_logic := 'X'; -- MISO
        dac_MOSI            : out std_logic;        -- MOSI
        dac_SCLK            : out std_logic;        -- SCLK
        dac_SS_n            : out std_logic_vector(1 downto 0);        -- SS_n
        spi_MISO            : in  std_logic := 'X'; -- MISO
        spi_MOSI            : out std_logic;        -- MOSI
        spi_SCLK            : out std_logic;        -- SCLK
        spi_SS_n            : out std_logic;        -- SS_n
        uart_rxd            : in  std_logic;
        uart_txd            : out std_logic;
        oc_i2c_scl_pad_o    : out std_logic;
        oc_i2c_scl_padoen_o : out std_logic;
        oc_i2c_sda_pad_i    : in  std_logic;
        oc_i2c_sda_pad_o    : out std_logic;
        oc_i2c_sda_padoen_o : out std_logic;
        oc_i2c_arst_i       : in  std_logic;
        oc_i2c_scl_pad_i    : in  std_logic;
        gpio_export         : out std_logic_vector(31 downto 0);
        xb_gpio_in_port                 : in  std_logic_vector(31 downto 0) := (others => 'X');
        xb_gpio_out_port                : out std_logic_vector(31 downto 0);
        xb_gpio_dir_export              : out std_logic_vector(31 downto 0);
        correction_rx_phase_gain_export : out std_logic_vector(31 downto 0);
        correction_tx_phase_gain_export : out std_logic_vector(31 downto 0);
        time_tamer_synchronize          : out std_logic;
        time_tamer_tx_clock             :   in  std_logic ;
        time_tamer_tx_reset             :   in  std_logic ;
        time_tamer_tx_time              :   in  std_logic_vector(63 downto 0);
        time_tamer_rx_clock             :   in  std_logic ;
        time_tamer_rx_reset             :   in  std_logic ;
        time_tamer_rx_time              :   in  std_logic_vector(63 downto 0);
		  
		  
		  pps_count_in_export				:   in std_logic_vector(31 downto 0);
		  pps_cfg_out_export 				:	 out std_logic_vector(7 downto 0);
		
		
		  xb_spi_gps_MISO		:	in		std_logic := 'X';
		  xb_spi_gps_MOSI		:	out	std_logic;
		  xb_spi_gps_SCLK		:	out	std_logic;
		  xb_spi_gps_SS_n		:	out	std_logic;
		  
		  xb_uart_gps_rxd		:	in		std_logic ;
		  xb_uart_gps_txd		:	out	std_logic 
      );
    end component nios_system;

    alias sys_rst   is fx3_ctl(7) ;
    alias tx_clock  is c4_tx_clock ;
    alias rx_clock  is lms_rx_clock_out ;

    type rx_mux_mode_t is (RX_MUX_NORMAL, RX_MUX_12BIT_COUNTER, RX_MUX_32BIT_COUNTER, RX_MUX_ENTROPY, RX_MUX_DIGITAL_LOOPBACK) ;

    signal rx_mux_sel       : unsigned(2 downto 0) ;
    signal rx_mux_mode      : rx_mux_mode_t ;

    signal \80MHz\          : std_logic ;
    signal \80MHz locked\   : std_logic ;

    signal nios_gpio        : std_logic_vector(31 downto 0) ;
    signal nios_xb_gpio_in  : std_logic_vector(31 downto 0) ;
    signal nios_xb_gpio_out : std_logic_vector(31 downto 0) ;
    signal nios_xb_gpio_dir : std_logic_vector(31 downto 0) ;
    signal xb_gpio_dir      : std_logic_vector(31 downto 0) ;

    signal correction_rx_phase_gain :  std_logic_vector(31 downto 0);
    signal correction_tx_phase_gain :  std_logic_vector(31 downto 0);

    signal i2c_scl_in       : std_logic ;
    signal i2c_scl_out      : std_logic ;
    signal i2c_scl_oen      : std_logic ;

    signal i2c_sda_in       : std_logic ;
    signal i2c_sda_out      : std_logic ;
    signal i2c_sda_oen      : std_logic ;

    type fifo_t is record
        aclr    :   std_logic ;

        wclock  :   std_logic ;
        wdata   :   std_logic_vector(31 downto 0) ;
        wreq    :   std_logic ;
        wempty  :   std_logic ;
        wfull   :   std_logic ;
        wused   :   std_logic_vector(11 downto 0) ;

        rclock  :   std_logic ;
        rdata   :   std_logic_vector(31 downto 0) ;
        rreq    :   std_logic ;
        rempty  :   std_logic ;
        rfull   :   std_logic ;
        rused   :   std_logic_vector(11 downto 0) ;
    end record ;

    signal rx_sample_fifo   : fifo_t ;
    signal tx_sample_fifo   : fifo_t ;

    type meta_fifo_tx_t is record
        aclr    :   std_logic ;

        wclock  :   std_logic ;
        wdata   :   std_logic_vector(31 downto 0) ;
        wreq    :   std_logic ;
        wempty  :   std_logic ;
        wfull   :   std_logic ;
        wused   :   std_logic_vector(4 downto 0) ;

        rclock  :   std_logic ;
        rdata   :   std_logic_vector(127 downto 0) ;
        rreq    :   std_logic ;
        rempty  :   std_logic ;
        rfull   :   std_logic ;
        rused   :   std_logic_vector(2 downto 0) ;
    end record ;
    signal tx_meta_fifo     : meta_fifo_tx_t ;

    type meta_fifo_rx_t is record
        aclr    :   std_logic ;

        wclock  :   std_logic ;
        wdata   :   std_logic_vector(127 downto 0) ;
        wreq    :   std_logic ;
        wempty  :   std_logic ;
        wfull   :   std_logic ;
        wused   :   std_logic_vector(4 downto 0) ;

        rclock  :   std_logic ;
        rdata   :   std_logic_vector(31 downto 0) ;
        rreq    :   std_logic ;
        rempty  :   std_logic ;
        rfull   :   std_logic ;
        rused   :   std_logic_vector(6 downto 0) ;
    end record ;
    signal rx_meta_fifo     : meta_fifo_rx_t ;

    signal sys_rst_sync     : std_logic ;

    signal usb_speed        : std_logic ;
    signal usb_speed_rx     : std_logic ;
    signal usb_speed_tx     : std_logic ;

    signal tx_reset         : std_logic ;
    signal rx_reset         : std_logic ;

    signal pclk_tx_enable   :   std_logic ;
    signal pclk_rx_enable   :   std_logic ;

    signal tx_enable        : std_logic ;
    signal rx_enable        : std_logic ;

    signal meta_en_tx       : std_logic ;
    signal meta_en_rx       : std_logic ;
    signal meta_en_fx3      : std_logic ;
    signal tx_timestamp     : unsigned(63 downto 0) ;
    signal rx_timestamp     : unsigned(63 downto 0) ;
    signal timestamp_sync   : std_logic ;

    signal rx_sample_i      : signed(15 downto 0) ;
    signal rx_sample_q      : signed(15 downto 0) ;
    signal rx_sample_valid  : std_logic ;

    signal rx_gen_mode      : std_logic ;
    signal rx_gen_i         : signed(15 downto 0) ;
    signal rx_gen_q         : signed(15 downto 0) ;
    signal rx_gen_valid     : std_logic ;

    signal rx_entropy_i     : signed(15 downto 0) := (others =>'0') ;
    signal rx_entropy_q     : signed(15 downto 0) := (others =>'0') ;
    signal rx_entropy_valid : std_logic := '0' ;

    signal tx_sample_raw_i : signed(15 downto 0);
    signal tx_sample_raw_q : signed(15 downto 0);
    signal tx_sample_raw_valid : std_logic;

    signal tx_sample_i      : signed(15 downto 0) ;
    signal tx_sample_q      : signed(15 downto 0) ;
    signal tx_sample_valid  : std_logic ;

    signal fx3_gpif_in      : std_logic_vector(31 downto 0) ;
    signal fx3_gpif_out     : std_logic_vector(31 downto 0) ;
    signal fx3_gpif_oe      : std_logic ;

    signal fx3_ctl_in       : std_logic_vector(12 downto 0) ;
    signal fx3_ctl_out      : std_logic_vector(12 downto 0) ;
    signal fx3_ctl_oe       : std_logic_vector(12 downto 0) ;

    signal nios_uart_rxd    :   std_logic ;
    signal nios_uart_txd    :   std_logic ;

    signal tx_underflow_led     :   std_logic ;
    signal tx_underflow_count   :   unsigned(63 downto 0) ;

    signal rx_overflow_led      :   std_logic ;
    signal rx_overflow_count    :   unsigned(63 downto 0) ;

    signal lms_rx_data_reg      :   signed(11 downto 0) ;
    signal lms_rx_iq_select_reg :   std_logic ;

    signal rx_mux_i             :   signed(15 downto 0) ;
    signal rx_mux_q             :   signed(15 downto 0) ;
    signal rx_mux_valid         :   std_logic ;

    signal rx_sample_corrected_i : signed(15 downto 0);
    signal rx_sample_corrected_q : signed(15 downto 0);
    signal rx_sample_corrected_valid : std_logic;

    signal led1_blink : std_logic;

    signal nios_sdo : std_logic;
    signal nios_sdio : std_logic;
    signal nios_sclk : std_logic;
    signal nios_ss_n : std_logic_vector(1 downto 0);
	 
	 --custom extra spi on xb -- 3.2mhz, 01 mode
	 signal nios_xb_spi_miso : std_logic;
	 signal nios_xb_spi_mosi : std_logic;
	 signal nios_xb_spi_clk : std_logic;
	 signal nios_xb_spi_cs : std_logic;
	 
	 signal nios_xb_uart_rxd : std_logic;
	 signal nios_xb_uart_txd : std_logic;
	 
	 --custom pps calibration signals
	 signal pps_calibration_clock_count : std_logic_vector(31 downto 0);
	 signal pps_calibration_config		: std_logic_vector(7 downto 0);
	 

    signal xb_mode  : std_logic_vector(1 downto 0);

    attribute keep of timestamp_sync : signal is true;
    attribute keep of rx_clock : signal is true;

    signal correction_valid : std_logic;

    signal correction_tx_phase :  signed(15 downto 0);--to_signed(integer(round(real(2**Q_SCALE) * PHASE_OFFSET)),DC_WIDTH);
    signal correction_tx_gain  :  signed(15 downto 0);--to_signed(integer(round(real(2**Q_SCALE) * DC_OFFSET_REAL)),DC_WIDTH);
    signal correction_rx_phase :  signed(15 downto 0);--to_signed(integer(round(real(2**Q_SCALE) * PHASE_OFFSET)),DC_WIDTH);
    signal correction_rx_gain  :  signed(15 downto 0);--to_signed(integer(round(real(2**Q_SCALE) * DC_OFFSET_REAL)),DC_WIDTH);

    constant FPGA_DC_CORRECTION :  signed(15 downto 0) := to_signed(integer(0), 16);

    signal fx3_pclk_pll     :   std_logic ;
    signal fx3_pll_locked   :   std_logic ;

    signal timestamp_req    :   std_logic ;
    signal timestamp_ack    :   std_logic ;
    signal fx3_timestamp    :   unsigned(63 downto 0) ;

begin

    correction_tx_phase <= signed(correction_tx_phase_gain(31 downto 16));
    correction_tx_gain  <= signed(correction_tx_phase_gain(15 downto 0));
    correction_rx_phase <= signed(correction_rx_phase_gain(31 downto 16));
    correction_rx_gain  <= signed(correction_rx_phase_gain(15 downto 0));
    correction_valid <= '1';


    -- Create 80MHz from 38.4MHz coming from the c4_clock source
    U_pll : entity work.pll
      port map (
        inclk0              =>  c4_clock,
        c0                  =>  \80MHz\,
        locked              =>  \80MHz locked\
      ) ;

    U_fx3_pll : entity work.fx3_pll
      port map (
        inclk0              =>  fx3_pclk,
        c0                  =>  fx3_pclk_pll,
        locked              =>  fx3_pll_locked
      ) ;

    -- Cross domain synchronizer chains
    U_usb_speed : entity work.synchronizer
      generic map (
        RESET_LEVEL         =>  '0'
      ) port map (
        reset               =>  '0',
        clock               =>  fx3_pclk_pll,
        async               =>  nios_gpio(7),
        sync                =>  usb_speed
      ) ;

    U_usb_speed_rx : entity work.synchronizer
      generic map (
        RESET_LEVEL         =>  '0'
      ) port map (
        reset               =>  '0',
        clock               =>  rx_clock,
        async               =>  nios_gpio(7),
        sync                =>  usb_speed_rx
      ) ;

    U_usb_speed_tx : entity work.synchronizer
      generic map (
        RESET_LEVEL         =>  '0'
      ) port map (
        reset               =>  '0',
        clock               =>  tx_clock,
        async               =>  nios_gpio(7),
        sync                =>  usb_speed_tx
      ) ;

    generate_mux_sel : for i in rx_mux_sel'range generate
        U_rx_source : entity work.synchronizer
          generic map (
            RESET_LEVEL         =>  '0'
          ) port map (
            reset               =>  '0',
            clock               =>  rx_clock,
            async               =>  nios_gpio(8+i),
            sync                =>  rx_mux_sel(i)
          ) ;
    end generate ;

    U_meta_sync_fx3 : entity work.synchronizer
      generic map (
        RESET_LEVEL         =>  '0'
      ) port map (
        reset               =>  '0',
        clock               =>  fx3_pclk_pll,
        async               =>  nios_gpio(16),
        sync                =>  meta_en_fx3
      ) ;

    U_meta_sync_tx : entity work.synchronizer
      generic map (
        RESET_LEVEL         =>  '0'
      ) port map (
        reset               =>  '0',
        clock               =>  tx_clock,
        async               =>  nios_gpio(16),
        sync                =>  meta_en_tx
      ) ;

    U_meta_sync_rx : entity work.synchronizer
      generic map (
        RESET_LEVEL         =>  '0'
      ) port map (
        reset               =>  '0',
        clock               =>  rx_clock,
        async               =>  nios_gpio(16),
        sync                =>  meta_en_rx
      ) ;

    xb_mode <= nios_gpio(31 downto 30);

    U_sys_reset_sync : entity work.reset_synchronizer
      generic map (
        INPUT_LEVEL         =>  '1',
        OUTPUT_LEVEL        =>  '1'
      ) port map (
        clock               =>  fx3_pclk_pll,
        async               =>  sys_rst,
        sync                =>  sys_rst_sync
      ) ;

    U_tx_reset : entity work.reset_synchronizer
      generic map (
        INPUT_LEVEL         =>  '1',
        OUTPUT_LEVEL        =>  '1'
      ) port map (
        clock               =>  c4_tx_clock,
        async               =>  sys_rst_sync,
        sync                =>  tx_reset
      ) ;

    U_rx_clock_reset : entity work.reset_synchronizer
      generic map (
        INPUT_LEVEL         =>  '1',
        OUTPUT_LEVEL        =>  '1'
      ) port map (
        clock               =>  rx_clock,
        async               =>  sys_rst_sync,
        sync                =>  rx_reset
      ) ;

    U_rx_enable_sync : entity work.synchronizer
      generic map (
        RESET_LEVEL =>  '0'
      ) port map (
        reset       =>  rx_reset,
        clock       =>  rx_clock,
        async       =>  pclk_rx_enable,
        sync        =>  rx_enable
      ) ;

    U_tx_enable_sync : entity work.synchronizer
      generic map (
        RESET_LEVEL =>  '0'
      ) port map (
        reset       =>  tx_reset,
        clock       =>  tx_clock,
        async       =>  pclk_tx_enable,
        sync        =>  tx_enable
      ) ;

    -- TX sample fifo
    tx_sample_fifo.aclr <= tx_reset ;
    tx_sample_fifo.wclock <= fx3_pclk_pll ;
    tx_sample_fifo.rclock <= tx_clock ;
    U_tx_sample_fifo : entity work.tx_fifo
      port map (
        aclr                => tx_sample_fifo.aclr,
        data                => tx_sample_fifo.wdata,
        rdclk               => tx_sample_fifo.rclock,
        rdreq               => tx_sample_fifo.rreq,
        wrclk               => tx_sample_fifo.wclock,
        wrreq               => tx_sample_fifo.wreq,
        q                   => tx_sample_fifo.rdata,
        rdempty             => tx_sample_fifo.rempty,
        rdfull              => tx_sample_fifo.rfull,
        rdusedw             => tx_sample_fifo.rused,
        wrempty             => tx_sample_fifo.wempty,
        wrfull              => tx_sample_fifo.wfull,
        wrusedw             => tx_sample_fifo.wused
      );

    -- TX meta fifo
    tx_meta_fifo.aclr <= tx_reset ;
    tx_meta_fifo.wclock <= fx3_pclk_pll ;
    tx_meta_fifo.rclock <= tx_clock ;
    U_tx_meta_fifo : entity work.tx_meta_fifo
      port map (
        aclr                => tx_meta_fifo.aclr,
        data                => tx_meta_fifo.wdata,
        rdclk               => tx_meta_fifo.rclock,
        rdreq               => tx_meta_fifo.rreq,
        wrclk               => tx_meta_fifo.wclock,
        wrreq               => tx_meta_fifo.wreq,
        q                   => tx_meta_fifo.rdata,
        rdempty             => tx_meta_fifo.rempty,
        rdfull              => tx_meta_fifo.rfull,
        rdusedw             => tx_meta_fifo.rused,
        wrempty             => tx_meta_fifo.wempty,
        wrfull              => tx_meta_fifo.wfull,
        wrusedw             => tx_meta_fifo.wused
      );

    -- RX sample fifo
    rx_sample_fifo.wclock <= rx_clock ;
    rx_sample_fifo.rclock <= fx3_pclk_pll ;
    U_rx_sample_fifo : entity work.rx_fifo
      port map (
        aclr                => rx_sample_fifo.aclr,
        data                => rx_sample_fifo.wdata,
        rdclk               => rx_sample_fifo.rclock,
        rdreq               => rx_sample_fifo.rreq,
        wrclk               => rx_sample_fifo.wclock,
        wrreq               => rx_sample_fifo.wreq,
        q                   => rx_sample_fifo.rdata,
        rdempty             => rx_sample_fifo.rempty,
        rdfull              => rx_sample_fifo.rfull,
        rdusedw             => rx_sample_fifo.rused,
        wrempty             => rx_sample_fifo.wempty,
        wrfull              => rx_sample_fifo.wfull,
        wrusedw             => rx_sample_fifo.wused
      );

    -- RX meta fifo
    rx_meta_fifo.aclr <= rx_reset ;
    rx_meta_fifo.wclock <= rx_clock ;
    rx_meta_fifo.rclock <= fx3_pclk_pll ;
    U_rx_meta_fifo : entity work.rx_meta_fifo
      port map (
        aclr                => rx_meta_fifo.aclr,
        data                => rx_meta_fifo.wdata,
        rdclk               => rx_meta_fifo.rclock,
        rdreq               => rx_meta_fifo.rreq,
        wrclk               => rx_meta_fifo.wclock,
        wrreq               => rx_meta_fifo.wreq,
        q                   => rx_meta_fifo.rdata,
        rdempty             => rx_meta_fifo.rempty,
        rdfull              => rx_meta_fifo.rfull,
        rdusedw             => rx_meta_fifo.rused,
        wrempty             => rx_meta_fifo.wempty,
        wrfull              => rx_meta_fifo.wfull,
        wrusedw             => rx_meta_fifo.wused
      );

    -- FX3 GPIF
    U_fx3_gpif : entity work.fx3_gpif
      port map (
        pclk                =>  fx3_pclk_pll,
        reset               =>  sys_rst_sync,

        usb_speed           =>  usb_speed,

        meta_enable         =>  meta_en_fx3,
        rx_enable           =>  pclk_rx_enable,
        tx_enable           =>  pclk_tx_enable,

        gpif_in             =>  fx3_gpif_in,
        gpif_out            =>  fx3_gpif_out,
        gpif_oe             =>  fx3_gpif_oe,
        ctl_in              =>  fx3_ctl_in,
        ctl_out             =>  fx3_ctl_out,
        ctl_oe              =>  fx3_ctl_oe,

        tx_fifo_write       =>  tx_sample_fifo.wreq,
        tx_fifo_full        =>  tx_sample_fifo.wfull,
        tx_fifo_empty       =>  tx_sample_fifo.wempty,
        tx_fifo_usedw       =>  tx_sample_fifo.wused,
        tx_fifo_data        =>  tx_sample_fifo.wdata,

        tx_timestamp        =>  fx3_timestamp,
        tx_meta_fifo_write  =>  tx_meta_fifo.wreq,
        tx_meta_fifo_full   =>  tx_meta_fifo.wfull,
        tx_meta_fifo_empty  =>  tx_meta_fifo.wempty,
        tx_meta_fifo_usedw  =>  tx_meta_fifo.wused,
        tx_meta_fifo_data   =>  tx_meta_fifo.wdata,


        rx_fifo_read        =>  rx_sample_fifo.rreq,
        rx_fifo_full        =>  rx_sample_fifo.rfull,
        rx_fifo_empty       =>  rx_sample_fifo.rempty,
        rx_fifo_usedw       =>  rx_sample_fifo.rused,
        rx_fifo_data        =>  rx_sample_fifo.rdata,

        rx_meta_fifo_read   =>  rx_meta_fifo.rreq,
        rx_meta_fifo_full   =>  rx_meta_fifo.rfull,
        rx_meta_fifo_empty  =>  rx_meta_fifo.rempty,
        rx_meta_fifo_usedr  =>  rx_meta_fifo.rused,
        rx_meta_fifo_data   =>  rx_meta_fifo.rdata
      ) ;

    -- Sample bridges
    U_fifo_writer : entity work.fifo_writer
      port map (
        clock               =>  rx_clock,
        reset               =>  rx_reset,
        enable              =>  rx_enable,

        usb_speed           =>  usb_speed_rx,
        meta_en             =>  meta_en_rx,
        timestamp           =>  rx_timestamp,

        fifo_clear          =>  rx_sample_fifo.aclr,
        fifo_full           =>  rx_sample_fifo.wfull,
        fifo_usedw          =>  rx_sample_fifo.wused,
        fifo_data           =>  rx_sample_fifo.wdata,
        fifo_write          =>  rx_sample_fifo.wreq,

        meta_fifo_full      =>  rx_meta_fifo.wfull,
        meta_fifo_usedw     =>  rx_meta_fifo.wused,
        meta_fifo_data      =>  rx_meta_fifo.wdata,
        meta_fifo_write     =>  rx_meta_fifo.wreq,

        in_i                =>  rx_sample_corrected_i,
        in_q                =>  rx_sample_corrected_q,
        in_valid            =>  rx_sample_corrected_valid,

        overflow_led        =>  rx_overflow_led,
        overflow_count      =>  rx_overflow_count,
        overflow_duration   =>  x"ffff"
      ) ;

    U_rx_iq_correction : entity work.iq_correction(rx)
      generic map(
        INPUT_WIDTH         => rx_sample_corrected_i'length
      ) port map(
        reset               => rx_reset,
        clock               => rx_clock,

        in_real             => resize(rx_mux_i,16),
        in_imag             => resize(rx_mux_q,16),
        in_valid            => rx_mux_valid,

        out_real            => rx_sample_corrected_i,
        out_imag            => rx_sample_corrected_q,
        out_valid           => rx_sample_corrected_valid,

        dc_real             => FPGA_DC_CORRECTION,
        dc_imag             => FPGA_DC_CORRECTION,
        gain                => correction_rx_gain,
        phase               => correction_rx_phase,
        correction_valid    => correction_valid
      );

    U_fifo_reader : entity work.fifo_reader
      port map (
        clock               =>  tx_clock,
        reset               =>  tx_reset,
        enable              =>  tx_enable,

        usb_speed           =>  usb_speed_tx,
        meta_en             =>  meta_en_tx,
        timestamp           =>  tx_timestamp,

        fifo_empty          =>  tx_sample_fifo.rempty,
        fifo_usedw          =>  tx_sample_fifo.rused,
        fifo_data           =>  tx_sample_fifo.rdata,
        fifo_read           =>  tx_sample_fifo.rreq,

        meta_fifo_empty     =>  tx_meta_fifo.rempty,
        meta_fifo_usedw     =>  tx_meta_fifo.rused,
        meta_fifo_data      =>  tx_meta_fifo.rdata,
        meta_fifo_read      =>  tx_meta_fifo.rreq,

        out_i               =>  tx_sample_raw_i,
        out_q               =>  tx_sample_raw_q,
        out_valid           =>  tx_sample_raw_valid,

        underflow_led       =>  tx_underflow_led,
        underflow_count     =>  tx_underflow_count,
        underflow_duration  =>  x"ffff"
      ) ;

    U_tx_iq_correction : entity work.iq_correction(tx)
      generic map (
        INPUT_WIDTH         => tx_sample_raw_i'length
      ) port map (
        reset               => tx_reset,
        clock               => tx_clock,

        in_real             => tx_sample_raw_i,
        in_imag             => tx_sample_raw_q,
        in_valid            => tx_sample_raw_valid,

        out_real            => tx_sample_i,
        out_imag            => tx_sample_q,
        out_valid           => tx_sample_valid,

        dc_real             => FPGA_DC_CORRECTION,
        dc_imag             => FPGA_DC_CORRECTION,
        gain                => correction_tx_gain,
        phase               => correction_tx_phase,
        correction_valid    => correction_valid
      );

    -- LMS6002D IQ interface
    rx_sample_i(15 downto 12) <= (others => rx_sample_i(11)) ;
    rx_sample_q(15 downto 12) <= (others => rx_sample_q(11)) ;
    U_lms6002d : entity work.lms6002d
      port map (
        rx_clock            =>  rx_clock,
        rx_reset            =>  rx_reset,
        rx_enable           =>  rx_enable,

        rx_lms_data         =>  lms_rx_data_reg,
        rx_lms_iq_sel       =>  lms_rx_iq_select_reg,
        rx_lms_enable       =>  open,

        rx_sample_i         =>  rx_sample_i(11 downto 0),
        rx_sample_q         =>  rx_sample_q(11 downto 0),
        rx_sample_valid     =>  rx_sample_valid,

        tx_clock            =>  tx_clock,
        tx_reset            =>  tx_reset,
        tx_enable           =>  tx_enable,

        tx_sample_i         =>  tx_sample_i(11 downto 0),
        tx_sample_q         =>  tx_sample_q(11 downto 0),
        tx_sample_valid     =>  tx_sample_valid,

        tx_lms_data         =>  lms_tx_data,
        tx_lms_iq_sel       =>  lms_tx_iq_select,
        tx_lms_enable       =>  open
      ) ;

    U_rx_siggen : entity work.signal_generator
      port map (
        clock           =>  rx_clock,
        reset           =>  rx_reset,
        enable          =>  rx_enable,

        mode            =>  rx_gen_mode,

        sample_i        =>  rx_gen_i,
        sample_q        =>  rx_gen_q,
        sample_valid    =>  rx_gen_valid
      ) ;

    rx_mux_mode <= rx_mux_mode_t'val(to_integer(rx_mux_sel)) ;

    rx_mux : process(rx_reset, rx_clock)
    begin
        if( rx_reset = '1' ) then
            rx_mux_i <= (others =>'0') ;
            rx_mux_q <= (others =>'0') ;
            rx_mux_valid <= '0' ;
            rx_gen_mode <= '0' ;
        elsif( rising_edge(rx_clock) ) then
            case rx_mux_mode is
                when RX_MUX_NORMAL =>
                    rx_mux_i <= rx_sample_i ;
                    rx_mux_q <= rx_sample_q ;
                    rx_mux_valid <= rx_sample_valid ;
                when RX_MUX_12BIT_COUNTER | RX_MUX_32BIT_COUNTER =>
                    rx_mux_i <= rx_gen_i ;
                    rx_mux_q <= rx_gen_q ;
                    rx_mux_valid <= rx_gen_valid ;
                    if( rx_mux_mode = RX_MUX_32BIT_COUNTER ) then
                        rx_gen_mode <= '1' ;
                    else
                        rx_gen_mode <= '0' ;
                    end if ;
                when RX_MUX_ENTROPY =>
                    rx_mux_i <= rx_entropy_i ;
                    rx_mux_q <= rx_entropy_q ;
                    rx_mux_valid <= rx_entropy_valid ;
                when RX_MUX_DIGITAL_LOOPBACK =>
                    rx_mux_i <= tx_sample_raw_i ;
                    rx_mux_q <= tx_sample_raw_q ;
                    rx_mux_valid <= tx_sample_raw_valid ;
                when others =>
                    rx_mux_i <= (others =>'0') ;
                    rx_mux_q <= (others =>'0') ;
                    rx_mux_valid <= '0' ;
            end case ;
        end if ;
    end process ;

    -- Register the inputs immediately
    lms_rx_data_reg         <= lms_rx_data when rising_edge(rx_clock) ;
    lms_rx_iq_select_reg    <= lms_rx_iq_select when rising_edge(rx_clock) ;

    -- FX3 GPIF bidirectional signals
    register_gpif : process(sys_rst_sync, fx3_pclk_pll)
    begin
        if( sys_rst_sync = '1' ) then
            fx3_gpif <= (others =>'Z') ;
            fx3_gpif_in <= (others =>'0') ;
        elsif( rising_edge(fx3_pclk_pll) ) then
            fx3_gpif_in <= fx3_gpif ;
            if( fx3_gpif_oe = '1' ) then
                fx3_gpif <= fx3_gpif_out ;
            else
                fx3_gpif <= (others =>'Z') ;
            end if ;
        end if ;
    end process ;

    generate_ctl : for i in fx3_ctl'range generate
        fx3_ctl(i) <= fx3_ctl_out(i) when fx3_ctl_oe(i) = '1' else 'Z';
    end generate ;

    fx3_ctl_in <= fx3_ctl ;

    nios_uart_txd <= fx3_uart_txd when sys_rst_sync = '0' else '1' ;
    fx3_uart_rxd <= nios_uart_rxd when sys_rst_sync = '0' else 'Z' ;
	 
	 
	 
	 
	 /* Add PPS Calibration Counter Component */
	 U_pps_counter : entity work.pps_calibration_counter
      port map (
        clock           =>  c4_clock,											/* Directly tied to the clock from the vcxto. 34.4 mhz? Considered 80 mhz from nios... */
        reset           =>  pps_calibration_config(7),
		  pps             =>  gps_ref_1pps,									   /* GPS pps calibration input - 1 sec pulse */
		  sample_size     =>  pps_calibration_config(6 downto 0),		/* 7 bit sample size setting */
	 
		  clock_count     =>  pps_calibration_clock_count		         /* The clock counts over the sample_size period */
			--data_ready		=>		--/* Not Connected */					/* High when count is ready. */
      ) ;

    -- NIOS control system for si5338, vctcxo trim and lms control
    U_nios_system : nios_system
      port map (
        clk_clk             => \80MHz\,
        reset_reset_n       => '1',
        dac_MISO            => nios_sdo,
        dac_MOSI            => nios_sdio,
        dac_SCLK            => nios_sclk,
        dac_SS_n            => nios_ss_n,
        spi_MISO            => lms_sdo,
        spi_MOSI            => lms_sdio,
        spi_SCLK            => lms_sclk,
        spi_SS_n            => lms_sen,
		  
		  xb_spi_gps_MISO		=> nios_xb_spi_miso,
		  xb_spi_gps_MOSI		=> nios_xb_spi_mosi,
		  xb_spi_gps_SCLK		=> nios_xb_spi_clk,
		  xb_spi_gps_SS_n		=> nios_xb_spi_cs,
		  
		  xb_uart_gps_rxd		=> nios_xb_uart_rxd,
		  xb_uart_gps_txd		=> nios_xb_uart_txd,
		  
        uart_rxd            => nios_uart_txd,
        uart_txd            => nios_uart_rxd,
        gpio_export         => nios_gpio,
        xb_gpio_in_port     => nios_xb_gpio_in,
        xb_gpio_out_port    => nios_xb_gpio_out,
        xb_gpio_dir_export  => nios_xb_gpio_dir,
        correction_tx_phase_gain_export    => correction_tx_phase_gain,
        correction_rx_phase_gain_export    => correction_rx_phase_gain,
        oc_i2c_scl_pad_o    => i2c_scl_out,
        oc_i2c_scl_padoen_o => i2c_scl_oen,
        oc_i2c_sda_pad_i    => i2c_sda_in,
        oc_i2c_sda_pad_o    => i2c_sda_out,
        oc_i2c_sda_padoen_o => i2c_sda_oen,
        oc_i2c_arst_i       => '0',
        oc_i2c_scl_pad_i    => i2c_scl_in,
        time_tamer_tx_clock             => tx_clock,
        time_tamer_tx_reset             => tx_reset,
        time_tamer_tx_time              => std_logic_vector(tx_timestamp),
        time_tamer_rx_clock             => rx_clock,
        time_tamer_rx_reset             => rx_reset,
        time_tamer_rx_time              => std_logic_vector(rx_timestamp),
        time_tamer_synchronize => timestamp_sync,
		  
		  
		  pps_count_in_export				=>   pps_calibration_clock_count,
		  pps_cfg_out_export 				=>	  pps_calibration_config
      ) ;

    xb_gpio_direction_proc : for i in 0 to 31 generate
        process(xb_gpio_dir, nios_xb_gpio_out, nios_xb_gpio_in, xb_mode, nios_ss_n)
        begin
            if (xb_gpio_dir(i) = '1') then
                nios_xb_gpio_in(i) <= nios_xb_gpio_out(i);
                if (i + 1 = 2) then
                    exp_gpio(i+1) <= '0';
                elsif (i + 1 /= 1) then
                    exp_gpio(i+1) <= nios_xb_gpio_out(i);
                end if;
            else
                if (i + 1 = 1) then
                    nios_xb_gpio_in(i) <= exp_clock_in;
                else
                    nios_xb_gpio_in(i) <= exp_gpio(i + 1);
                    exp_gpio(i + 1) <= 'Z';
                end if;
            end if;
        end process;
    end generate ;

    nios_gpio(20 downto 19) <= nios_ss_n;
    nios_gpio(22 downto 21) <= xb_mode;
    process(all)
    begin
        if( xb_mode = "00" ) then
            xb_gpio_dir <= nios_xb_gpio_dir(31 downto 0);
            dac_sclk <= nios_sclk;
            dac_csx <= nios_ss_n(0);
            nios_sdo <= dac_sdo;
            dac_sdi <= nios_sdio;
				
            -- missing 30-32
        elsif( xb_mode = "10" ) then
            xb_gpio_dir <= nios_xb_gpio_dir(31 downto 0);
            if (nios_ss_n(1 downto 0) = "10") then --
                dac_sclk <= nios_sclk;
                dac_csx <= '0';
                nios_sdo <= dac_sdo;
                dac_sdi <= nios_sdio;
            elsif (nios_ss_n(1 downto 0) = "01") then
                dac_csx <= '1';
            else
                dac_csx <= '1';
            end if;
        else
            xb_gpio_dir <= nios_xb_gpio_dir(31 downto 0)  ;
        end if;
    end process;

    -- IO for NIOS
    si_scl <= i2c_scl_out when i2c_scl_oen = '0' else 'Z' ;
    si_sda <= i2c_sda_out when i2c_sda_oen = '0' else 'Z' ;

    i2c_scl_in <= si_scl ;
    i2c_sda_in <= si_sda ;

    toggle_led1 : process(fx3_pclk_pll)
        variable count : natural range 0 to 100_000_000 := 100_000_000 ;
    begin
        if( rising_edge(fx3_pclk_pll) ) then
            count := count - 1 ;
            if( count = 0 ) then
                count := 100_000_00 ;
                led1_blink <= not led1_blink;
            end if ;
        end if ;
    end process ;

    led(1) <= led1_blink        when nios_gpio(15) = '0' else not nios_gpio(12);			-- LED2
    led(2) <= tx_underflow_led  when nios_gpio(15) = '0' else not nios_gpio(13);
    --led(3) <= rx_overflow_led   when nios_gpio(15) = '0' else not nios_gpio(14);
	 led(3) <= not gps_ref_1pps   when nios_gpio(15) = '0' else not nios_gpio(14);				--LED3

--    toggle_led2 : process(rx_clock)
--        variable count : natural range 0 to 38_400_00 := 38_400_00 ;
--    begin
--        if( rising_edge(rx_clock) ) then
--            count := count - 1 ;
--            if( count = 0 ) then
--                count := 38_400_00 ;
--                led(2) <= not led(2) ;
--            end if ;
--        end if ;
--    end process ;
--
--    toggle_led3 : process(rx_clock)
--        variable count : natural range 0 to 19_200_000 := 19_200_000 ;
--    begin
--        if( rising_edge(rx_clock) ) then
--            count := count - 1 ;
--            if( count = 0 ) then
--                count := 19_200_000 ;
--                led(3) <= not led(3) ;
--            end if ;
--        end if ;
--    end process ;

    lms_reset               <= nios_gpio(0) ;

    lms_rx_enable           <= nios_gpio(1) ;
    lms_tx_enable           <= nios_gpio(2) ;

    lms_tx_v                <= nios_gpio(4 downto 3) ;
    lms_rx_v                <= nios_gpio(6 downto 5) ;

    -- CTS and the SPI CSx are tied to the same signal.  When we are in reset, allow for SPI accesses
    fx3_uart_cts            <= '1' when sys_rst_sync = '0' else 'Z'  ;

    exp_spi_clock           <= nios_xb_spi_clk;		--nios_sclk when ( nios_ss_n(1 downto 0) = "01" ) else '0' ;
    exp_spi_mosi            <= nios_xb_spi_mosi;	--nios_sdio when ( nios_ss_n(1 downto 0) = "01" ) else '0' ;
    exp_spi_cs <= nios_xb_spi_cs;
    nios_xb_spi_miso        <= exp_spi_miso;	
    --exp_gpio                <= (others =>'Z') ;
	 
	 exp_uart_tx				<= nios_xb_uart_txd;
	 nios_xb_uart_rxd			<= exp_uart_rx;

    mini_exp1               <= 'Z';
    mini_exp2               <= 'Z';

    increment_tx_time : process(tx_clock, tx_reset)
        variable tock : boolean := false ;
    begin
        if( tx_reset = '1') then
            tx_timestamp <= (others => '0');
            tock := false ;
        elsif( rising_edge( tx_clock )) then
            if (meta_en_tx = '0') then
                tx_timestamp <= (others => '0');
            else
                if( nios_gpio(17) = '0' or tock = true) then
                tx_timestamp <= tx_timestamp + 1;
            end if;
        end if;
            tock := not tock ;
        end if;
    end process;

    increment_rx_time : process(rx_clock, rx_reset)
        variable tock : boolean := false ;
    begin
        if( rx_reset = '1') then
            rx_timestamp <= (others => '0');
            tock := false ;
        elsif( rising_edge( rx_clock )) then
            if (meta_en_rx = '0') then
                rx_timestamp <= (others => '0');
            else
                if( nios_gpio(17) = '0' or tock = true ) then
                rx_timestamp <= rx_timestamp + 1;
            end if;
        end if;
            tock := not tock ;
        end if;
    end process;

    drive_handshake : process(fx3_pclk_pll, sys_rst_sync)
    begin
        if( sys_rst_sync = '1' ) then
            timestamp_req <= '0' ;
        elsif( rising_edge(fx3_pclk_pll) ) then
            if( meta_en_fx3 = '0' ) then
                timestamp_req <= '0' ;
            else
                if( timestamp_ack = '0' ) then
                    timestamp_req <= '1' ;
                elsif( timestamp_ack = '1' ) then
                    timestamp_req <= '0' ;
                end if ;
            end if ;
        end if ;
    end process ;

    U_timestamp_handshake : entity work.handshake
      generic map (
        DATA_WIDTH          =>  tx_timestamp'length
      ) port map (
        source_clock        =>  tx_clock,
        source_reset        =>  tx_reset,
        source_data         =>  std_logic_vector(tx_timestamp),

        dest_clock          =>  fx3_pclk_pll,
        dest_reset          =>  sys_rst_sync,
        unsigned(dest_data) =>  fx3_timestamp,
        dest_req            =>  timestamp_req,
        dest_ack            =>  timestamp_ack
      ) ;

end architecture ; -- arch

