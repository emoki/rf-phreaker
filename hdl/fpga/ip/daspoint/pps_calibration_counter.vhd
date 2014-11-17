
	-- Author: Cameron Karlsson
	-- Created: November 15 2014
	
	-- Description:
	-- Counts the clock ticks over a number of gps pps calibration inputs. Outputs the ticks
	-- when the number of pulses have been received.


library ieee;
    use ieee.std_logic_1164.all ;
    use ieee.numeric_std.all ;
    use ieee.math_real.all;

entity pps_calibration_counter is
  port (
    clock           :   in      std_logic ;					--/* System clock input to count */
    reset           :   in      std_logic ;					--/* Apply a falling edge to clear state and begin a new sample */
	 pps             :   in      std_logic ;					--/* GPS pps calibration input - 1 sec pulse */
	 sample_size     :   in     std_logic_vector(6 downto 0) ;		--/* 7 bit sample size setting */
	 
    clock_count     :   out     std_logic_vector(31 downto 0)		--/* The clock counts over the sample_size period */
  ) ;
end entity ;

architecture arch of pps_calibration_counter is
	signal data_ready   :  std_logic ;				--	/* High when sample is complete - after sample_size pulses */
begin
	
    counter : process(clock, reset, pps)
        variable tickcount32        :   unsigned(31 downto 0) ;
        variable pulsecount7        :   unsigned(6 downto 0) ;
		  variable samplesize7        :   unsigned(6 downto 0) ;
		  variable firstpulse			:	 std_logic ;				 -- high once first pps pulse occurs and counting begins
    begin
        if( reset = '1' ) then
            tickcount32 := (others =>'0') ;
				pulsecount7 := (others =>'0') ;
				clock_count <= (others => '0');
            data_ready <= '0' ;
            firstpulse := '0' ;
				samplesize7 := unsigned(sample_size) ;
        else
             
				 if (data_ready = '0') then 
						if ( firstpulse = '1' and falling_edge(clock)) then
							tickcount32 := tickcount32 + 1 ;
						end if;
						
						if( rising_edge(pps)) then
							firstpulse := '1';
							pulsecount7 := pulsecount7 + 1;
							if(pulsecount7 > samplesize7) then
								data_ready <= '1';
							end if;
						end if;
						clock_count(31 downto 7) <= (others => '0');
						clock_count(6 downto 0) <= std_logic_vector(samplesize7);
				 else 
					   clock_count <= std_logic_vector(tickcount32);
				 end if;
				 
        end if ;
		  
		  
    end process ;

end architecture ;
