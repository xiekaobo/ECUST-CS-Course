library ieee;
use ieee.std_logic_1164.all;
entity led_disp is
port(
     datain:in std_logic_vector(3 downto 0);
     dataout:out std_logic_vector(7 downto 0)
    );
end led_disp;

architecture rtl of led_disp is
begin
 process(datain)
  begin
  case datain is
  when "0000"=>dataout<="00111111";--0
  when "0001"=>dataout<="00000110";--1
  when "0010"=>dataout<="01011011";--2
  when "0011"=>dataout<="01001111";--3
  when "0100"=>dataout<="01100110";--4
  when "0101"=>dataout<="01101101";--5
  when "0110"=>dataout<="01111101";--6
  when "0111"=>dataout<="00000111";--7
  when "1000"=>dataout<="01111111";--8
  when "1001"=>dataout<="01101111";--9
  when "1010"=>dataout<="01000000";--间隔横杠
  when "1011"=>dataout<="01000000";--间隔横杠
  when "1100"=>dataout<="00000000";--超出范围就不显示停住，直到正确为止
  when others=>null; ---千万注意！！！！！！不能为11111111，否则出错，会有空显示产生
  end case;
 end process;
end rtl;
