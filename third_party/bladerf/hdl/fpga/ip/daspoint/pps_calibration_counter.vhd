
	-- Author: Cameron Karlsson
	-- Created: November 15 2014
	
	-- Description:
	-- Counts the clock ticks over a number of gps pps calibration inputs. Outputs the ticks
	-- when the number of pulses have been received, otherwise 0.


library ieee;
    use ieee.std_logic_1164.all ;
    use ieee.numeric_std.all ;
    use ieee.math_real.all;

entity pps_calibration_counter is
  port (
		clock				:	in		std_logic ;					--/* System clock input to count */
		reset				:	in		std_logic ;					--/* Apply a falling edge to clear state and begin a new sample */
		pps				:	in		std_logic ;					--/* GPS pps calibration input - 1 sec pulse */
		sample_size		:	in		std_logic_vector(6 downto 0) ;		--/* 7 bit sample size setting */
	 
		clock_count		:	out		std_logic_vector(31 downto 0);		--/* The clock counts over the sample_size period */
		data_ready		:	out		std_logic 				--	/* High when sample is complete - after sample_size pulses */
  ) ;
end entity ;

architecture arch of pps_calibration_counter is
	signal s_tickcount32		:  unsigned(31 downto 0) ;
	signal s_pulsecount7		:  unsigned(6 downto 0) ;
	signal s_samplesize7 		:  unsigned(6 downto 0) ;
	signal s_firstpulse		:	std_logic ;				 -- high once first pps pulse occurs and counting begins
begin
	
    counter : process(clock, reset, pps)
        
    begin
        if( reset = '1' ) then
				s_tickcount32	<= (others =>'0') ;
				s_pulsecount7	<= (others =>'0') ;
				clock_count		<= (others => '0');
				data_ready		<= '0' ;
				s_firstpulse	<= '0' ;
				s_samplesize7 	<= unsigned(sample_size) ;
        else
             
				if (s_pulsecount7 <= s_samplesize7) then 
						if ( s_firstpulse = '1' and rising_edge(clock)) then
							s_tickcount32 <= s_tickcount32 + 1 ;
						end if;
						
						if( rising_edge(pps)) then
							s_firstpulse 	<= '1';
							s_pulsecount7 	<= s_pulsecount7 + 1;
						end if;
						clock_count <= (others => '0');
				else 
					clock_count 	<= std_logic_vector(s_tickcount32);
					data_ready 		<= '1';
				end if;
				 
        end if ;
		  
		  
    end process ;

end architecture ;
