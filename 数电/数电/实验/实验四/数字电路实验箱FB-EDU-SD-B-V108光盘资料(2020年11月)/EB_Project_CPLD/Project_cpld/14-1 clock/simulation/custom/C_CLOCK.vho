-- Copyright (C) 1991-2009 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II"
-- VERSION "Version 9.0 Build 235 06/17/2009 Service Pack 2 SJ Web Edition"

-- DATE "06/26/2018 11:53:54"

-- 
-- Device: Altera EPM240T100C5 Package TQFP100
-- 

-- 
-- This VHDL file should be used for Custom VHDL only
-- 

LIBRARY IEEE, maxii;
USE IEEE.std_logic_1164.all;
USE maxii.maxii_components.all;

ENTITY 	C_CLOCK IS
    PORT (
	clk : IN std_logic;
	ctrlin : IN std_logic_vector(2 DOWNTO 0);
	disp : OUT std_logic_vector(7 DOWNTO 0);
	ledcs : OUT std_logic_vector(3 DOWNTO 0)
	);
END C_CLOCK;

ARCHITECTURE structure OF C_CLOCK IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_clk : std_logic;
SIGNAL ww_ctrlin : std_logic_vector(2 DOWNTO 0);
SIGNAL ww_disp : std_logic_vector(7 DOWNTO 0);
SIGNAL ww_ledcs : std_logic_vector(3 DOWNTO 0);
SIGNAL \timeclk~regout\ : std_logic;
SIGNAL \Add3~1\ : std_logic;
SIGNAL \Add3~0_combout\ : std_logic;
SIGNAL \Add3~3\ : std_logic;
SIGNAL \Add3~3COUT1_86\ : std_logic;
SIGNAL \Add3~2_combout\ : std_logic;
SIGNAL \Add3~5\ : std_logic;
SIGNAL \Add3~5COUT1_88\ : std_logic;
SIGNAL \Add3~4_combout\ : std_logic;
SIGNAL \Add3~7\ : std_logic;
SIGNAL \Add3~7COUT1_90\ : std_logic;
SIGNAL \Add3~6_combout\ : std_logic;
SIGNAL \LessThan3~0_combout\ : std_logic;
SIGNAL \Add3~9\ : std_logic;
SIGNAL \Add3~9COUT1_84\ : std_logic;
SIGNAL \Add3~8_combout\ : std_logic;
SIGNAL \Add3~11\ : std_logic;
SIGNAL \Add3~11COUT1_92\ : std_logic;
SIGNAL \Add3~10_combout\ : std_logic;
SIGNAL \Add3~13\ : std_logic;
SIGNAL \Add3~12_combout\ : std_logic;
SIGNAL \Add3~15\ : std_logic;
SIGNAL \Add3~15COUT1_94\ : std_logic;
SIGNAL \Add3~14_combout\ : std_logic;
SIGNAL \Add3~17\ : std_logic;
SIGNAL \Add3~17COUT1_96\ : std_logic;
SIGNAL \Add3~16_combout\ : std_logic;
SIGNAL \LessThan3~1_combout\ : std_logic;
SIGNAL \LessThan3~2_combout\ : std_logic;
SIGNAL \Add3~19\ : std_logic;
SIGNAL \Add3~19COUT1_98\ : std_logic;
SIGNAL \Add3~18_combout\ : std_logic;
SIGNAL \Add3~21\ : std_logic;
SIGNAL \Add3~21COUT1_100\ : std_logic;
SIGNAL \Add3~20_combout\ : std_logic;
SIGNAL \LessThan3~3_combout\ : std_logic;
SIGNAL \Add3~23\ : std_logic;
SIGNAL \Add3~22_combout\ : std_logic;
SIGNAL \Add3~25\ : std_logic;
SIGNAL \Add3~25COUT1_102\ : std_logic;
SIGNAL \Add3~24_combout\ : std_logic;
SIGNAL \Add3~27\ : std_logic;
SIGNAL \Add3~27COUT1_104\ : std_logic;
SIGNAL \Add3~26_combout\ : std_logic;
SIGNAL \Add3~29\ : std_logic;
SIGNAL \Add3~29COUT1_106\ : std_logic;
SIGNAL \Add3~28_combout\ : std_logic;
SIGNAL \Add3~31\ : std_logic;
SIGNAL \Add3~31COUT1_108\ : std_logic;
SIGNAL \Add3~30_combout\ : std_logic;
SIGNAL \Add3~33\ : std_logic;
SIGNAL \Add3~32_combout\ : std_logic;
SIGNAL \LessThan3~4_combout\ : std_logic;
SIGNAL \LessThan3~5_combout\ : std_logic;
SIGNAL \Add3~35\ : std_logic;
SIGNAL \Add3~35COUT1_110\ : std_logic;
SIGNAL \Add3~34_combout\ : std_logic;
SIGNAL \Add3~37\ : std_logic;
SIGNAL \Add3~37COUT1_112\ : std_logic;
SIGNAL \Add3~36_combout\ : std_logic;
SIGNAL \Add3~38_combout\ : std_logic;
SIGNAL \process_3:cnt[7]~regout\ : std_logic;
SIGNAL \process_3:cnt[8]~regout\ : std_logic;
SIGNAL \process_3:cnt[9]~regout\ : std_logic;
SIGNAL \process_3:cnt[10]~regout\ : std_logic;
SIGNAL \process_3:cnt[6]~regout\ : std_logic;
SIGNAL \Add3~41\ : std_logic;
SIGNAL \Add3~41COUT1_82\ : std_logic;
SIGNAL \Add3~40_combout\ : std_logic;
SIGNAL \process_3:cnt[11]~regout\ : std_logic;
SIGNAL \process_3:cnt[12]~regout\ : std_logic;
SIGNAL \process_3:cnt[13]~regout\ : std_logic;
SIGNAL \process_3:cnt[14]~regout\ : std_logic;
SIGNAL \process_3:cnt[15]~regout\ : std_logic;
SIGNAL \process_3:cnt[16]~regout\ : std_logic;
SIGNAL \process_3:cnt[17]~regout\ : std_logic;
SIGNAL \process_3:cnt[18]~regout\ : std_logic;
SIGNAL \process_3:cnt[19]~regout\ : std_logic;
SIGNAL \process_3:cnt[20]~regout\ : std_logic;
SIGNAL \process_3:cnt[21]~regout\ : std_logic;
SIGNAL \process_3:cnt[22]~regout\ : std_logic;
SIGNAL \process_3:cnt[23]~regout\ : std_logic;
SIGNAL \process_3:cnt[24]~regout\ : std_logic;
SIGNAL \process_3:cnt[25]~regout\ : std_logic;
SIGNAL \LessThan4~0_combout\ : std_logic;
SIGNAL \LessThan4~1_combout\ : std_logic;
SIGNAL \cnt~156_combout\ : std_logic;
SIGNAL \process_3:cnt[5]~regout\ : std_logic;
SIGNAL \Add3~43\ : std_logic;
SIGNAL \Add3~43COUT1_80\ : std_logic;
SIGNAL \Add3~42_combout\ : std_logic;
SIGNAL \process_3:cnt[4]~regout\ : std_logic;
SIGNAL \Add3~45\ : std_logic;
SIGNAL \Add3~45COUT1_78\ : std_logic;
SIGNAL \Add3~44_combout\ : std_logic;
SIGNAL \process_3:cnt[3]~regout\ : std_logic;
SIGNAL \Add3~47\ : std_logic;
SIGNAL \Add3~46_combout\ : std_logic;
SIGNAL \process_3:cnt[2]~regout\ : std_logic;
SIGNAL \Add3~49\ : std_logic;
SIGNAL \Add3~49COUT1_76\ : std_logic;
SIGNAL \Add3~48_combout\ : std_logic;
SIGNAL \process_3:cnt[1]~regout\ : std_logic;
SIGNAL \Add3~51\ : std_logic;
SIGNAL \Add3~51COUT1_74\ : std_logic;
SIGNAL \Add3~50_combout\ : std_logic;
SIGNAL \process_3:cnt[0]~regout\ : std_logic;
SIGNAL \clk~combout\ : std_logic;
SIGNAL \Equal0~0_combout\ : std_logic;
SIGNAL \cnt[0]~189\ : std_logic;
SIGNAL \cnt[1]~186\ : std_logic;
SIGNAL \cnt[1]~186COUT1_211\ : std_logic;
SIGNAL \cnt[2]~182\ : std_logic;
SIGNAL \cnt[2]~182COUT1_213\ : std_logic;
SIGNAL \cnt[3]~178\ : std_logic;
SIGNAL \cnt[3]~178COUT1_215\ : std_logic;
SIGNAL \cnt[4]~154\ : std_logic;
SIGNAL \cnt[4]~154COUT1_217\ : std_logic;
SIGNAL \cnt[5]~123\ : std_logic;
SIGNAL \cnt[6]~125\ : std_logic;
SIGNAL \cnt[6]~125COUT1_219\ : std_logic;
SIGNAL \cnt[7]~119\ : std_logic;
SIGNAL \cnt[7]~119COUT1_221\ : std_logic;
SIGNAL \cnt[8]~121\ : std_logic;
SIGNAL \cnt[8]~121COUT1_223\ : std_logic;
SIGNAL \cnt[9]~117\ : std_logic;
SIGNAL \cnt[9]~117COUT1_225\ : std_logic;
SIGNAL \cnt[10]~115\ : std_logic;
SIGNAL \cnt[11]~127\ : std_logic;
SIGNAL \cnt[11]~127COUT1_227\ : std_logic;
SIGNAL \cnt[12]~129\ : std_logic;
SIGNAL \cnt[12]~129COUT1_229\ : std_logic;
SIGNAL \cnt[13]~113\ : std_logic;
SIGNAL \cnt[13]~113COUT1_231\ : std_logic;
SIGNAL \cnt[14]~131\ : std_logic;
SIGNAL \cnt[14]~131COUT1_233\ : std_logic;
SIGNAL \cnt[15]~133\ : std_logic;
SIGNAL \cnt[16]~135\ : std_logic;
SIGNAL \cnt[16]~135COUT1_235\ : std_logic;
SIGNAL \cnt[17]~109\ : std_logic;
SIGNAL \cnt[17]~109COUT1_237\ : std_logic;
SIGNAL \cnt[18]~111\ : std_logic;
SIGNAL \cnt[18]~111COUT1_239\ : std_logic;
SIGNAL \cnt[19]~137\ : std_logic;
SIGNAL \cnt[19]~137COUT1_241\ : std_logic;
SIGNAL \LessThan0~3_combout\ : std_logic;
SIGNAL \LessThan0~0_combout\ : std_logic;
SIGNAL \LessThan0~1_combout\ : std_logic;
SIGNAL \LessThan0~2_combout\ : std_logic;
SIGNAL \LessThan0~4_combout\ : std_logic;
SIGNAL \LessThan0~6_combout\ : std_logic;
SIGNAL \cnt[20]~139\ : std_logic;
SIGNAL \LessThan0~5_combout\ : std_logic;
SIGNAL \key_temp0[2]~3_combout\ : std_logic;
SIGNAL \process_4~1\ : std_logic;
SIGNAL \LessThan5~0_combout\ : std_logic;
SIGNAL \Mux2~0\ : std_logic;
SIGNAL \sec10[3]~8\ : std_logic;
SIGNAL \min1[3]~13_combout\ : std_logic;
SIGNAL \data[3]~17_combout\ : std_logic;
SIGNAL \data[3]~18_combout\ : std_logic;
SIGNAL \data~21_combout\ : std_logic;
SIGNAL \LessThan7~0_combout\ : std_logic;
SIGNAL \min10[3]~17_combout\ : std_logic;
SIGNAL \data[3]~16_combout\ : std_logic;
SIGNAL \data~23_combout\ : std_logic;
SIGNAL \data~19_combout\ : std_logic;
SIGNAL \u|Mux7~0_combout\ : std_logic;
SIGNAL \u|Mux0~3_combout\ : std_logic;
SIGNAL \u|Mux1~3_combout\ : std_logic;
SIGNAL \u|Mux2~3_combout\ : std_logic;
SIGNAL \u|Mux3~3_combout\ : std_logic;
SIGNAL \u|Mux4~3_combout\ : std_logic;
SIGNAL \u|Mux5~3_combout\ : std_logic;
SIGNAL \u|Mux6~3_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[8]~regout\ : std_logic;
SIGNAL \Add1~30_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[0]~regout\ : std_logic;
SIGNAL \Add1~31\ : std_logic;
SIGNAL \Add1~31COUT1_46\ : std_logic;
SIGNAL \Add1~28_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[1]~regout\ : std_logic;
SIGNAL \Add1~29\ : std_logic;
SIGNAL \Add1~29COUT1_48\ : std_logic;
SIGNAL \Add1~26_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[2]~regout\ : std_logic;
SIGNAL \Add1~27\ : std_logic;
SIGNAL \Add1~8_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[3]~regout\ : std_logic;
SIGNAL \Add1~9\ : std_logic;
SIGNAL \Add1~9COUT1_50\ : std_logic;
SIGNAL \Add1~10_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[4]~regout\ : std_logic;
SIGNAL \Add1~11\ : std_logic;
SIGNAL \Add1~11COUT1_52\ : std_logic;
SIGNAL \Add1~12_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[5]~regout\ : std_logic;
SIGNAL \Add1~13\ : std_logic;
SIGNAL \Add1~13COUT1_54\ : std_logic;
SIGNAL \Add1~14_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[6]~regout\ : std_logic;
SIGNAL \Add1~15\ : std_logic;
SIGNAL \Add1~15COUT1_56\ : std_logic;
SIGNAL \Add1~16_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[7]~regout\ : std_logic;
SIGNAL \Add1~17\ : std_logic;
SIGNAL \Add1~18_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[9]~regout\ : std_logic;
SIGNAL \Add1~19\ : std_logic;
SIGNAL \Add1~19COUT1_58\ : std_logic;
SIGNAL \Add1~0_combout\ : std_logic;
SIGNAL \LessThan2~1_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[10]~regout\ : std_logic;
SIGNAL \Add1~1\ : std_logic;
SIGNAL \Add1~1COUT1_60\ : std_logic;
SIGNAL \Add1~2_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[11]~regout\ : std_logic;
SIGNAL \Add1~3\ : std_logic;
SIGNAL \Add1~3COUT1_62\ : std_logic;
SIGNAL \Add1~4_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[12]~regout\ : std_logic;
SIGNAL \Add1~5\ : std_logic;
SIGNAL \Add1~5COUT1_64\ : std_logic;
SIGNAL \Add1~6_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[13]~regout\ : std_logic;
SIGNAL \Add1~7\ : std_logic;
SIGNAL \Add1~20_combout\ : std_logic;
SIGNAL \LessThan2~0_combout\ : std_logic;
SIGNAL \LessThan2~2_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[14]~regout\ : std_logic;
SIGNAL \Add1~21\ : std_logic;
SIGNAL \Add1~21COUT1_66\ : std_logic;
SIGNAL \Add1~22_combout\ : std_logic;
SIGNAL \CLK_1Khz:cnt[15]~regout\ : std_logic;
SIGNAL \Add1~23\ : std_logic;
SIGNAL \Add1~23COUT1_68\ : std_logic;
SIGNAL \Add1~24_combout\ : std_logic;
SIGNAL \LessThan1~1_combout\ : std_logic;
SIGNAL \LessThan1~0_combout\ : std_logic;
SIGNAL \LessThan1~2_combout\ : std_logic;
SIGNAL \clk_1k~regout\ : std_logic;
SIGNAL \ledcs[0]~reg0_regout\ : std_logic;
SIGNAL \ledcs[1]~reg0_regout\ : std_logic;
SIGNAL \ledcs[2]~reg0_regout\ : std_logic;
SIGNAL \ledcs[3]~reg0_regout\ : std_logic;
SIGNAL \u|dataout\ : std_logic_vector(7 DOWNTO 0);
SIGNAL cnt : std_logic_vector(21 DOWNTO 0);
SIGNAL cnt2 : std_logic_vector(3 DOWNTO 0);
SIGNAL \ctrlin~combout\ : std_logic_vector(2 DOWNTO 0);
SIGNAL data : std_logic_vector(3 DOWNTO 0);
SIGNAL key_temp0 : std_logic_vector(2 DOWNTO 0);
SIGNAL min1 : std_logic_vector(3 DOWNTO 0);
SIGNAL min10 : std_logic_vector(3 DOWNTO 0);
SIGNAL sec1 : std_logic_vector(3 DOWNTO 0);
SIGNAL sec10 : std_logic_vector(3 DOWNTO 0);

BEGIN

ww_clk <= clk;
ww_ctrlin <= ctrlin;
disp <= ww_disp;
ledcs <= ww_ledcs;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\clk~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_clk,
	combout => \clk~combout\);

timeclk : maxii_lcell
-- Equation(s):
-- \timeclk~regout\ = DFFEAS(!\Add3~38_combout\ & (!\Add3~34_combout\ & \LessThan3~5_combout\ # !\Add3~36_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1303",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add3~34_combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~36_combout\,
	datad => \LessThan3~5_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \timeclk~regout\);

\Add3~0\ : maxii_lcell
-- Equation(s):
-- \Add3~0_combout\ = \process_3:cnt[7]~regout\ $ (!\Add3~47\ & \Add3~9\) # (\Add3~47\ & \Add3~9COUT1_84\)
-- \Add3~1\ = CARRY(!\Add3~9COUT1_84\ # !\process_3:cnt[7]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[7]~regout\,
	cin => \Add3~47\,
	cin0 => \Add3~9\,
	cin1 => \Add3~9COUT1_84\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~0_combout\,
	cout => \Add3~1\);

\Add3~2\ : maxii_lcell
-- Equation(s):
-- \Add3~2_combout\ = \process_3:cnt[8]~regout\ $ !\Add3~1\
-- \Add3~3\ = CARRY(\process_3:cnt[8]~regout\ & !\Add3~1\)
-- \Add3~3COUT1_86\ = CARRY(\process_3:cnt[8]~regout\ & !\Add3~1\)

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[8]~regout\,
	cin => \Add3~1\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~2_combout\,
	cout0 => \Add3~3\,
	cout1 => \Add3~3COUT1_86\);

\Add3~4\ : maxii_lcell
-- Equation(s):
-- \Add3~4_combout\ = \process_3:cnt[9]~regout\ $ (!\Add3~1\ & \Add3~3\) # (\Add3~1\ & \Add3~3COUT1_86\)
-- \Add3~5\ = CARRY(!\Add3~3\ # !\process_3:cnt[9]~regout\)
-- \Add3~5COUT1_88\ = CARRY(!\Add3~3COUT1_86\ # !\process_3:cnt[9]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[9]~regout\,
	cin => \Add3~1\,
	cin0 => \Add3~3\,
	cin1 => \Add3~3COUT1_86\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~4_combout\,
	cout0 => \Add3~5\,
	cout1 => \Add3~5COUT1_88\);

\Add3~6\ : maxii_lcell
-- Equation(s):
-- \Add3~6_combout\ = \process_3:cnt[10]~regout\ $ (!(!\Add3~1\ & \Add3~5\) # (\Add3~1\ & \Add3~5COUT1_88\))
-- \Add3~7\ = CARRY(\process_3:cnt[10]~regout\ & (!\Add3~5\))
-- \Add3~7COUT1_90\ = CARRY(\process_3:cnt[10]~regout\ & (!\Add3~5COUT1_88\))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "a50a",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \process_3:cnt[10]~regout\,
	cin => \Add3~1\,
	cin0 => \Add3~5\,
	cin1 => \Add3~5COUT1_88\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~6_combout\,
	cout0 => \Add3~7\,
	cout1 => \Add3~7COUT1_90\);

\LessThan3~0\ : maxii_lcell
-- Equation(s):
-- \LessThan3~0_combout\ = !\Add3~2_combout\ & !\Add3~4_combout\ & !\Add3~6_combout\ & !\Add3~0_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~2_combout\,
	datab => \Add3~4_combout\,
	datac => \Add3~6_combout\,
	datad => \Add3~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan3~0_combout\);

\Add3~8\ : maxii_lcell
-- Equation(s):
-- \Add3~8_combout\ = \process_3:cnt[6]~regout\ $ !(!\Add3~47\ & \Add3~41\) # (\Add3~47\ & \Add3~41COUT1_82\)
-- \Add3~9\ = CARRY(\process_3:cnt[6]~regout\ & !\Add3~41\)
-- \Add3~9COUT1_84\ = CARRY(\process_3:cnt[6]~regout\ & !\Add3~41COUT1_82\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[6]~regout\,
	cin => \Add3~47\,
	cin0 => \Add3~41\,
	cin1 => \Add3~41COUT1_82\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~8_combout\,
	cout0 => \Add3~9\,
	cout1 => \Add3~9COUT1_84\);

\Add3~10\ : maxii_lcell
-- Equation(s):
-- \Add3~10_combout\ = \process_3:cnt[11]~regout\ $ ((!\Add3~1\ & \Add3~7\) # (\Add3~1\ & \Add3~7COUT1_90\))
-- \Add3~11\ = CARRY(!\Add3~7\ # !\process_3:cnt[11]~regout\)
-- \Add3~11COUT1_92\ = CARRY(!\Add3~7COUT1_90\ # !\process_3:cnt[11]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \process_3:cnt[11]~regout\,
	cin => \Add3~1\,
	cin0 => \Add3~7\,
	cin1 => \Add3~7COUT1_90\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~10_combout\,
	cout0 => \Add3~11\,
	cout1 => \Add3~11COUT1_92\);

\Add3~12\ : maxii_lcell
-- Equation(s):
-- \Add3~12_combout\ = \process_3:cnt[12]~regout\ $ !(!\Add3~1\ & \Add3~11\) # (\Add3~1\ & \Add3~11COUT1_92\)
-- \Add3~13\ = CARRY(\process_3:cnt[12]~regout\ & !\Add3~11COUT1_92\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[12]~regout\,
	cin => \Add3~1\,
	cin0 => \Add3~11\,
	cin1 => \Add3~11COUT1_92\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~12_combout\,
	cout => \Add3~13\);

\Add3~14\ : maxii_lcell
-- Equation(s):
-- \Add3~14_combout\ = \process_3:cnt[13]~regout\ $ \Add3~13\
-- \Add3~15\ = CARRY(!\Add3~13\ # !\process_3:cnt[13]~regout\)
-- \Add3~15COUT1_94\ = CARRY(!\Add3~13\ # !\process_3:cnt[13]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[13]~regout\,
	cin => \Add3~13\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~14_combout\,
	cout0 => \Add3~15\,
	cout1 => \Add3~15COUT1_94\);

\Add3~16\ : maxii_lcell
-- Equation(s):
-- \Add3~16_combout\ = \process_3:cnt[14]~regout\ $ !(!\Add3~13\ & \Add3~15\) # (\Add3~13\ & \Add3~15COUT1_94\)
-- \Add3~17\ = CARRY(\process_3:cnt[14]~regout\ & !\Add3~15\)
-- \Add3~17COUT1_96\ = CARRY(\process_3:cnt[14]~regout\ & !\Add3~15COUT1_94\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[14]~regout\,
	cin => \Add3~13\,
	cin0 => \Add3~15\,
	cin1 => \Add3~15COUT1_94\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~16_combout\,
	cout0 => \Add3~17\,
	cout1 => \Add3~17COUT1_96\);

\LessThan3~1\ : maxii_lcell
-- Equation(s):
-- \LessThan3~1_combout\ = \Add3~14_combout\ & (\Add3~16_combout\ & \Add3~12_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~14_combout\,
	datac => \Add3~16_combout\,
	datad => \Add3~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan3~1_combout\);

\LessThan3~2\ : maxii_lcell
-- Equation(s):
-- \LessThan3~2_combout\ = !\Add3~8_combout\ & \LessThan3~0_combout\ # !\LessThan3~1_combout\ # !\Add3~10_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "7f3f",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~8_combout\,
	datab => \Add3~10_combout\,
	datac => \LessThan3~1_combout\,
	datad => \LessThan3~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan3~2_combout\);

\Add3~18\ : maxii_lcell
-- Equation(s):
-- \Add3~18_combout\ = \process_3:cnt[15]~regout\ $ (!\Add3~13\ & \Add3~17\) # (\Add3~13\ & \Add3~17COUT1_96\)
-- \Add3~19\ = CARRY(!\Add3~17\ # !\process_3:cnt[15]~regout\)
-- \Add3~19COUT1_98\ = CARRY(!\Add3~17COUT1_96\ # !\process_3:cnt[15]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[15]~regout\,
	cin => \Add3~13\,
	cin0 => \Add3~17\,
	cin1 => \Add3~17COUT1_96\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~18_combout\,
	cout0 => \Add3~19\,
	cout1 => \Add3~19COUT1_98\);

\Add3~20\ : maxii_lcell
-- Equation(s):
-- \Add3~20_combout\ = \process_3:cnt[16]~regout\ $ !(!\Add3~13\ & \Add3~19\) # (\Add3~13\ & \Add3~19COUT1_98\)
-- \Add3~21\ = CARRY(\process_3:cnt[16]~regout\ & !\Add3~19\)
-- \Add3~21COUT1_100\ = CARRY(\process_3:cnt[16]~regout\ & !\Add3~19COUT1_98\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[16]~regout\,
	cin => \Add3~13\,
	cin0 => \Add3~19\,
	cin1 => \Add3~19COUT1_98\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~20_combout\,
	cout0 => \Add3~21\,
	cout1 => \Add3~21COUT1_100\);

\LessThan3~3\ : maxii_lcell
-- Equation(s):
-- \LessThan3~3_combout\ = !\Add3~18_combout\ & \LessThan3~2_combout\ # !\Add3~20_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3f0f",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \Add3~18_combout\,
	datac => \Add3~20_combout\,
	datad => \LessThan3~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan3~3_combout\);

\Add3~22\ : maxii_lcell
-- Equation(s):
-- \Add3~22_combout\ = \process_3:cnt[17]~regout\ $ (!\Add3~13\ & \Add3~21\) # (\Add3~13\ & \Add3~21COUT1_100\)
-- \Add3~23\ = CARRY(!\Add3~21COUT1_100\ # !\process_3:cnt[17]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[17]~regout\,
	cin => \Add3~13\,
	cin0 => \Add3~21\,
	cin1 => \Add3~21COUT1_100\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~22_combout\,
	cout => \Add3~23\);

\Add3~24\ : maxii_lcell
-- Equation(s):
-- \Add3~24_combout\ = \process_3:cnt[18]~regout\ $ (!\Add3~23\)
-- \Add3~25\ = CARRY(\process_3:cnt[18]~regout\ & (!\Add3~23\))
-- \Add3~25COUT1_102\ = CARRY(\process_3:cnt[18]~regout\ & (!\Add3~23\))

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "a50a",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \process_3:cnt[18]~regout\,
	cin => \Add3~23\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~24_combout\,
	cout0 => \Add3~25\,
	cout1 => \Add3~25COUT1_102\);

\Add3~26\ : maxii_lcell
-- Equation(s):
-- \Add3~26_combout\ = \process_3:cnt[19]~regout\ $ (!\Add3~23\ & \Add3~25\) # (\Add3~23\ & \Add3~25COUT1_102\)
-- \Add3~27\ = CARRY(!\Add3~25\ # !\process_3:cnt[19]~regout\)
-- \Add3~27COUT1_104\ = CARRY(!\Add3~25COUT1_102\ # !\process_3:cnt[19]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[19]~regout\,
	cin => \Add3~23\,
	cin0 => \Add3~25\,
	cin1 => \Add3~25COUT1_102\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~26_combout\,
	cout0 => \Add3~27\,
	cout1 => \Add3~27COUT1_104\);

\Add3~28\ : maxii_lcell
-- Equation(s):
-- \Add3~28_combout\ = \process_3:cnt[20]~regout\ $ !(!\Add3~23\ & \Add3~27\) # (\Add3~23\ & \Add3~27COUT1_104\)
-- \Add3~29\ = CARRY(\process_3:cnt[20]~regout\ & !\Add3~27\)
-- \Add3~29COUT1_106\ = CARRY(\process_3:cnt[20]~regout\ & !\Add3~27COUT1_104\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[20]~regout\,
	cin => \Add3~23\,
	cin0 => \Add3~27\,
	cin1 => \Add3~27COUT1_104\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~28_combout\,
	cout0 => \Add3~29\,
	cout1 => \Add3~29COUT1_106\);

\Add3~30\ : maxii_lcell
-- Equation(s):
-- \Add3~30_combout\ = \process_3:cnt[21]~regout\ $ (!\Add3~23\ & \Add3~29\) # (\Add3~23\ & \Add3~29COUT1_106\)
-- \Add3~31\ = CARRY(!\Add3~29\ # !\process_3:cnt[21]~regout\)
-- \Add3~31COUT1_108\ = CARRY(!\Add3~29COUT1_106\ # !\process_3:cnt[21]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[21]~regout\,
	cin => \Add3~23\,
	cin0 => \Add3~29\,
	cin1 => \Add3~29COUT1_106\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~30_combout\,
	cout0 => \Add3~31\,
	cout1 => \Add3~31COUT1_108\);

\Add3~32\ : maxii_lcell
-- Equation(s):
-- \Add3~32_combout\ = \process_3:cnt[22]~regout\ $ (!(!\Add3~23\ & \Add3~31\) # (\Add3~23\ & \Add3~31COUT1_108\))
-- \Add3~33\ = CARRY(\process_3:cnt[22]~regout\ & (!\Add3~31COUT1_108\))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "a50a",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \process_3:cnt[22]~regout\,
	cin => \Add3~23\,
	cin0 => \Add3~31\,
	cin1 => \Add3~31COUT1_108\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~32_combout\,
	cout => \Add3~33\);

\LessThan3~4\ : maxii_lcell
-- Equation(s):
-- \LessThan3~4_combout\ = \Add3~32_combout\ & \Add3~30_combout\ & \Add3~26_combout\ & \Add3~28_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~32_combout\,
	datab => \Add3~30_combout\,
	datac => \Add3~26_combout\,
	datad => \Add3~28_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan3~4_combout\);

\LessThan3~5\ : maxii_lcell
-- Equation(s):
-- \LessThan3~5_combout\ = !\Add3~22_combout\ & \LessThan3~3_combout\ # !\LessThan3~4_combout\ # !\Add3~24_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "7f3f",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~22_combout\,
	datab => \Add3~24_combout\,
	datac => \LessThan3~4_combout\,
	datad => \LessThan3~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan3~5_combout\);

\Add3~34\ : maxii_lcell
-- Equation(s):
-- \Add3~34_combout\ = \process_3:cnt[23]~regout\ $ (\Add3~33\)
-- \Add3~35\ = CARRY(!\Add3~33\ # !\process_3:cnt[23]~regout\)
-- \Add3~35COUT1_110\ = CARRY(!\Add3~33\ # !\process_3:cnt[23]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \process_3:cnt[23]~regout\,
	cin => \Add3~33\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~34_combout\,
	cout0 => \Add3~35\,
	cout1 => \Add3~35COUT1_110\);

\Add3~36\ : maxii_lcell
-- Equation(s):
-- \Add3~36_combout\ = \process_3:cnt[24]~regout\ $ (!(!\Add3~33\ & \Add3~35\) # (\Add3~33\ & \Add3~35COUT1_110\))
-- \Add3~37\ = CARRY(\process_3:cnt[24]~regout\ & (!\Add3~35\))
-- \Add3~37COUT1_112\ = CARRY(\process_3:cnt[24]~regout\ & (!\Add3~35COUT1_110\))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "a50a",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \process_3:cnt[24]~regout\,
	cin => \Add3~33\,
	cin0 => \Add3~35\,
	cin1 => \Add3~35COUT1_110\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~36_combout\,
	cout0 => \Add3~37\,
	cout1 => \Add3~37COUT1_112\);

\Add3~38\ : maxii_lcell
-- Equation(s):
-- \Add3~38_combout\ = (!\Add3~33\ & \Add3~37\) # (\Add3~33\ & \Add3~37COUT1_112\) $ \process_3:cnt[25]~regout\

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "0ff0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datad => \process_3:cnt[25]~regout\,
	cin => \Add3~33\,
	cin0 => \Add3~37\,
	cin1 => \Add3~37COUT1_112\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~38_combout\);

\process_3:cnt[7]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[7]~regout\ = DFFEAS(\Add3~0_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa0a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add3~0_combout\,
	datac => \Add3~38_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[7]~regout\);

\process_3:cnt[8]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[8]~regout\ = DFFEAS(\Add3~2_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~2_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[8]~regout\);

\process_3:cnt[9]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[9]~regout\ = DFFEAS(\Add3~4_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc0c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~4_combout\,
	datac => \Add3~38_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[9]~regout\);

\process_3:cnt[10]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[10]~regout\ = DFFEAS(\Add3~6_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~6_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[10]~regout\);

\process_3:cnt[6]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[6]~regout\ = DFFEAS(\Add3~8_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~8_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[6]~regout\);

\Add3~40\ : maxii_lcell
-- Equation(s):
-- \Add3~40_combout\ = \process_3:cnt[5]~regout\ $ ((!\Add3~47\ & \Add3~43\) # (\Add3~47\ & \Add3~43COUT1_80\))
-- \Add3~41\ = CARRY(!\Add3~43\ # !\process_3:cnt[5]~regout\)
-- \Add3~41COUT1_82\ = CARRY(!\Add3~43COUT1_80\ # !\process_3:cnt[5]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \process_3:cnt[5]~regout\,
	cin => \Add3~47\,
	cin0 => \Add3~43\,
	cin1 => \Add3~43COUT1_80\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~40_combout\,
	cout0 => \Add3~41\,
	cout1 => \Add3~41COUT1_82\);

\process_3:cnt[11]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[11]~regout\ = DFFEAS(\Add3~10_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~10_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[11]~regout\);

\process_3:cnt[12]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[12]~regout\ = DFFEAS(\Add3~12_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~12_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[12]~regout\);

\process_3:cnt[13]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[13]~regout\ = DFFEAS(\Add3~14_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f300",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \cnt~156_combout\,
	datad => \Add3~14_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[13]~regout\);

\process_3:cnt[14]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[14]~regout\ = DFFEAS(\Add3~16_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa22",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add3~16_combout\,
	datab => \Add3~38_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[14]~regout\);

\process_3:cnt[15]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[15]~regout\ = DFFEAS(\Add3~18_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~18_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[15]~regout\);

\process_3:cnt[16]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[16]~regout\ = DFFEAS(\Add3~20_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~20_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[16]~regout\);

\process_3:cnt[17]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[17]~regout\ = DFFEAS(\Add3~22_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f300",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \cnt~156_combout\,
	datad => \Add3~22_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[17]~regout\);

\process_3:cnt[18]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[18]~regout\ = DFFEAS(\Add3~24_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~24_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[18]~regout\);

\process_3:cnt[19]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[19]~regout\ = DFFEAS(\Add3~26_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc0c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~26_combout\,
	datac => \Add3~38_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[19]~regout\);

\process_3:cnt[20]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[20]~regout\ = DFFEAS(\Add3~28_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~28_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[20]~regout\);

\process_3:cnt[21]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[21]~regout\ = DFFEAS(\Add3~30_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f300",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \cnt~156_combout\,
	datad => \Add3~30_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[21]~regout\);

\process_3:cnt[22]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[22]~regout\ = DFFEAS(\Add3~32_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f300",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \cnt~156_combout\,
	datad => \Add3~32_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[22]~regout\);

\process_3:cnt[23]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[23]~regout\ = DFFEAS(\Add3~34_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa22",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add3~34_combout\,
	datab => \Add3~38_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[23]~regout\);

\process_3:cnt[24]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[24]~regout\ = DFFEAS(\Add3~36_combout\ & !\Add3~38_combout\, GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00f0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datac => \Add3~36_combout\,
	datad => \Add3~38_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[24]~regout\);

\process_3:cnt[25]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[25]~regout\ = DFFEAS(\Add3~38_combout\ & \cnt~156_combout\, GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c0c0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[25]~regout\);

\LessThan4~0\ : maxii_lcell
-- Equation(s):
-- \LessThan4~0_combout\ = !\Add3~10_combout\ & \LessThan3~0_combout\ # !\LessThan3~1_combout\ # !\Add3~18_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "7f3f",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~10_combout\,
	datab => \Add3~18_combout\,
	datac => \LessThan3~1_combout\,
	datad => \LessThan3~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan4~0_combout\);

\LessThan4~1\ : maxii_lcell
-- Equation(s):
-- \LessThan4~1_combout\ = !\Add3~24_combout\ & (!\Add3~20_combout\ & \LessThan4~0_combout\ # !\Add3~22_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1303",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~20_combout\,
	datab => \Add3~24_combout\,
	datac => \Add3~22_combout\,
	datad => \LessThan4~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan4~1_combout\);

\cnt~156\ : maxii_lcell
-- Equation(s):
-- \cnt~156_combout\ = !\Add3~36_combout\ & (\LessThan4~1_combout\ # !\LessThan3~4_combout\ # !\Add3~34_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3313",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~34_combout\,
	datab => \Add3~36_combout\,
	datac => \LessThan3~4_combout\,
	datad => \LessThan4~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \cnt~156_combout\);

\process_3:cnt[5]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[5]~regout\ = DFFEAS(\Add3~40_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~40_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[5]~regout\);

\Add3~42\ : maxii_lcell
-- Equation(s):
-- \Add3~42_combout\ = \process_3:cnt[4]~regout\ $ !(!\Add3~47\ & \Add3~45\) # (\Add3~47\ & \Add3~45COUT1_78\)
-- \Add3~43\ = CARRY(\process_3:cnt[4]~regout\ & !\Add3~45\)
-- \Add3~43COUT1_80\ = CARRY(\process_3:cnt[4]~regout\ & !\Add3~45COUT1_78\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[4]~regout\,
	cin => \Add3~47\,
	cin0 => \Add3~45\,
	cin1 => \Add3~45COUT1_78\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~42_combout\,
	cout0 => \Add3~43\,
	cout1 => \Add3~43COUT1_80\);

\process_3:cnt[4]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[4]~regout\ = DFFEAS(\Add3~42_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a2a2",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add3~42_combout\,
	datab => \Add3~38_combout\,
	datac => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[4]~regout\);

\Add3~44\ : maxii_lcell
-- Equation(s):
-- \Add3~44_combout\ = \process_3:cnt[3]~regout\ $ \Add3~47\
-- \Add3~45\ = CARRY(!\Add3~47\ # !\process_3:cnt[3]~regout\)
-- \Add3~45COUT1_78\ = CARRY(!\Add3~47\ # !\process_3:cnt[3]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[3]~regout\,
	cin => \Add3~47\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~44_combout\,
	cout0 => \Add3~45\,
	cout1 => \Add3~45COUT1_78\);

\process_3:cnt[3]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[3]~regout\ = DFFEAS(\Add3~44_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~44_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[3]~regout\);

\Add3~46\ : maxii_lcell
-- Equation(s):
-- \Add3~46_combout\ = \process_3:cnt[2]~regout\ $ !\Add3~49\
-- \Add3~47\ = CARRY(\process_3:cnt[2]~regout\ & !\Add3~49COUT1_76\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[2]~regout\,
	cin0 => \Add3~49\,
	cin1 => \Add3~49COUT1_76\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~46_combout\,
	cout => \Add3~47\);

\process_3:cnt[2]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[2]~regout\ = DFFEAS(\Add3~46_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~46_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[2]~regout\);

\Add3~48\ : maxii_lcell
-- Equation(s):
-- \Add3~48_combout\ = \process_3:cnt[1]~regout\ $ \Add3~51\
-- \Add3~49\ = CARRY(!\Add3~51\ # !\process_3:cnt[1]~regout\)
-- \Add3~49COUT1_76\ = CARRY(!\Add3~51COUT1_74\ # !\process_3:cnt[1]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[1]~regout\,
	cin0 => \Add3~51\,
	cin1 => \Add3~51COUT1_74\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~48_combout\,
	cout0 => \Add3~49\,
	cout1 => \Add3~49COUT1_76\);

\process_3:cnt[1]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[1]~regout\ = DFFEAS(\Add3~48_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~48_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[1]~regout\);

\Add3~50\ : maxii_lcell
-- Equation(s):
-- \Add3~50_combout\ = !\process_3:cnt[0]~regout\
-- \Add3~51\ = CARRY(\process_3:cnt[0]~regout\)
-- \Add3~51COUT1_74\ = CARRY(\process_3:cnt[0]~regout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33cc",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \process_3:cnt[0]~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add3~50_combout\,
	cout0 => \Add3~51\,
	cout1 => \Add3~51COUT1_74\);

\process_3:cnt[0]\ : maxii_lcell
-- Equation(s):
-- \process_3:cnt[0]~regout\ = DFFEAS(\Add3~50_combout\ & (\cnt~156_combout\ # !\Add3~38_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => \Add3~38_combout\,
	datac => \Add3~50_combout\,
	datad => \cnt~156_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \process_3:cnt[0]~regout\);

\ctrlin[0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_ctrlin(0),
	combout => \ctrlin~combout\(0));

\ctrlin[1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_ctrlin(1),
	combout => \ctrlin~combout\(1));

\ctrlin[2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_ctrlin(2),
	combout => \ctrlin~combout\(2));

\Equal0~0\ : maxii_lcell
-- Equation(s):
-- \Equal0~0_combout\ = \ctrlin~combout\(0) & \ctrlin~combout\(1) & (\ctrlin~combout\(2))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8800",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ctrlin~combout\(0),
	datab => \ctrlin~combout\(1),
	datad => \ctrlin~combout\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Equal0~0_combout\);

\cnt[0]\ : maxii_lcell
-- Equation(s):
-- cnt(0) = DFFEAS(!cnt(0), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[0]~189\ = CARRY(cnt(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "55aa",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(0),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(0),
	cout => \cnt[0]~189\);

\cnt[1]\ : maxii_lcell
-- Equation(s):
-- cnt(1) = DFFEAS(cnt(1) $ (\cnt[0]~189\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[1]~186\ = CARRY(!\cnt[0]~189\ # !cnt(1))
-- \cnt[1]~186COUT1_211\ = CARRY(!\cnt[0]~189\ # !cnt(1))

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(1),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[0]~189\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(1),
	cout0 => \cnt[1]~186\,
	cout1 => \cnt[1]~186COUT1_211\);

\cnt[2]\ : maxii_lcell
-- Equation(s):
-- cnt(2) = DFFEAS(cnt(2) $ (!(!\cnt[0]~189\ & \cnt[1]~186\) # (\cnt[0]~189\ & \cnt[1]~186COUT1_211\)), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[2]~182\ = CARRY(cnt(2) & (!\cnt[1]~186\))
-- \cnt[2]~182COUT1_213\ = CARRY(cnt(2) & (!\cnt[1]~186COUT1_211\))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "a50a",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(2),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[0]~189\,
	cin0 => \cnt[1]~186\,
	cin1 => \cnt[1]~186COUT1_211\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(2),
	cout0 => \cnt[2]~182\,
	cout1 => \cnt[2]~182COUT1_213\);

\cnt[3]\ : maxii_lcell
-- Equation(s):
-- cnt(3) = DFFEAS(cnt(3) $ (!\cnt[0]~189\ & \cnt[2]~182\) # (\cnt[0]~189\ & \cnt[2]~182COUT1_213\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[3]~178\ = CARRY(!\cnt[2]~182\ # !cnt(3))
-- \cnt[3]~178COUT1_215\ = CARRY(!\cnt[2]~182COUT1_213\ # !cnt(3))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => cnt(3),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[0]~189\,
	cin0 => \cnt[2]~182\,
	cin1 => \cnt[2]~182COUT1_213\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(3),
	cout0 => \cnt[3]~178\,
	cout1 => \cnt[3]~178COUT1_215\);

\cnt[4]\ : maxii_lcell
-- Equation(s):
-- cnt(4) = DFFEAS(cnt(4) $ (!(!\cnt[0]~189\ & \cnt[3]~178\) # (\cnt[0]~189\ & \cnt[3]~178COUT1_215\)), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[4]~154\ = CARRY(cnt(4) & (!\cnt[3]~178\))
-- \cnt[4]~154COUT1_217\ = CARRY(cnt(4) & (!\cnt[3]~178COUT1_215\))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "a50a",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(4),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[0]~189\,
	cin0 => \cnt[3]~178\,
	cin1 => \cnt[3]~178COUT1_215\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(4),
	cout0 => \cnt[4]~154\,
	cout1 => \cnt[4]~154COUT1_217\);

\cnt[5]\ : maxii_lcell
-- Equation(s):
-- cnt(5) = DFFEAS(cnt(5) $ (!\cnt[0]~189\ & \cnt[4]~154\) # (\cnt[0]~189\ & \cnt[4]~154COUT1_217\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[5]~123\ = CARRY(!\cnt[4]~154COUT1_217\ # !cnt(5))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => cnt(5),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[0]~189\,
	cin0 => \cnt[4]~154\,
	cin1 => \cnt[4]~154COUT1_217\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(5),
	cout => \cnt[5]~123\);

\cnt[6]\ : maxii_lcell
-- Equation(s):
-- cnt(6) = DFFEAS(cnt(6) $ !\cnt[5]~123\, GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[6]~125\ = CARRY(cnt(6) & !\cnt[5]~123\)
-- \cnt[6]~125COUT1_219\ = CARRY(cnt(6) & !\cnt[5]~123\)

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => cnt(6),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[5]~123\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(6),
	cout0 => \cnt[6]~125\,
	cout1 => \cnt[6]~125COUT1_219\);

\cnt[7]\ : maxii_lcell
-- Equation(s):
-- cnt(7) = DFFEAS(cnt(7) $ (!\cnt[5]~123\ & \cnt[6]~125\) # (\cnt[5]~123\ & \cnt[6]~125COUT1_219\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[7]~119\ = CARRY(!\cnt[6]~125\ # !cnt(7))
-- \cnt[7]~119COUT1_221\ = CARRY(!\cnt[6]~125COUT1_219\ # !cnt(7))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => cnt(7),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[5]~123\,
	cin0 => \cnt[6]~125\,
	cin1 => \cnt[6]~125COUT1_219\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(7),
	cout0 => \cnt[7]~119\,
	cout1 => \cnt[7]~119COUT1_221\);

\cnt[8]\ : maxii_lcell
-- Equation(s):
-- cnt(8) = DFFEAS(cnt(8) $ !(!\cnt[5]~123\ & \cnt[7]~119\) # (\cnt[5]~123\ & \cnt[7]~119COUT1_221\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[8]~121\ = CARRY(cnt(8) & !\cnt[7]~119\)
-- \cnt[8]~121COUT1_223\ = CARRY(cnt(8) & !\cnt[7]~119COUT1_221\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => cnt(8),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[5]~123\,
	cin0 => \cnt[7]~119\,
	cin1 => \cnt[7]~119COUT1_221\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(8),
	cout0 => \cnt[8]~121\,
	cout1 => \cnt[8]~121COUT1_223\);

\cnt[9]\ : maxii_lcell
-- Equation(s):
-- cnt(9) = DFFEAS(cnt(9) $ ((!\cnt[5]~123\ & \cnt[8]~121\) # (\cnt[5]~123\ & \cnt[8]~121COUT1_223\)), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[9]~117\ = CARRY(!\cnt[8]~121\ # !cnt(9))
-- \cnt[9]~117COUT1_225\ = CARRY(!\cnt[8]~121COUT1_223\ # !cnt(9))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(9),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[5]~123\,
	cin0 => \cnt[8]~121\,
	cin1 => \cnt[8]~121COUT1_223\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(9),
	cout0 => \cnt[9]~117\,
	cout1 => \cnt[9]~117COUT1_225\);

\cnt[10]\ : maxii_lcell
-- Equation(s):
-- cnt(10) = DFFEAS(cnt(10) $ (!(!\cnt[5]~123\ & \cnt[9]~117\) # (\cnt[5]~123\ & \cnt[9]~117COUT1_225\)), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[10]~115\ = CARRY(cnt(10) & (!\cnt[9]~117COUT1_225\))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "a50a",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(10),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[5]~123\,
	cin0 => \cnt[9]~117\,
	cin1 => \cnt[9]~117COUT1_225\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(10),
	cout => \cnt[10]~115\);

\cnt[11]\ : maxii_lcell
-- Equation(s):
-- cnt(11) = DFFEAS(cnt(11) $ (\cnt[10]~115\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[11]~127\ = CARRY(!\cnt[10]~115\ # !cnt(11))
-- \cnt[11]~127COUT1_227\ = CARRY(!\cnt[10]~115\ # !cnt(11))

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(11),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[10]~115\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(11),
	cout0 => \cnt[11]~127\,
	cout1 => \cnt[11]~127COUT1_227\);

\cnt[12]\ : maxii_lcell
-- Equation(s):
-- cnt(12) = DFFEAS(cnt(12) $ (!(!\cnt[10]~115\ & \cnt[11]~127\) # (\cnt[10]~115\ & \cnt[11]~127COUT1_227\)), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[12]~129\ = CARRY(cnt(12) & (!\cnt[11]~127\))
-- \cnt[12]~129COUT1_229\ = CARRY(cnt(12) & (!\cnt[11]~127COUT1_227\))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "a50a",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(12),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[10]~115\,
	cin0 => \cnt[11]~127\,
	cin1 => \cnt[11]~127COUT1_227\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(12),
	cout0 => \cnt[12]~129\,
	cout1 => \cnt[12]~129COUT1_229\);

\cnt[13]\ : maxii_lcell
-- Equation(s):
-- cnt(13) = DFFEAS(cnt(13) $ (!\cnt[10]~115\ & \cnt[12]~129\) # (\cnt[10]~115\ & \cnt[12]~129COUT1_229\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[13]~113\ = CARRY(!\cnt[12]~129\ # !cnt(13))
-- \cnt[13]~113COUT1_231\ = CARRY(!\cnt[12]~129COUT1_229\ # !cnt(13))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => cnt(13),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[10]~115\,
	cin0 => \cnt[12]~129\,
	cin1 => \cnt[12]~129COUT1_229\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(13),
	cout0 => \cnt[13]~113\,
	cout1 => \cnt[13]~113COUT1_231\);

\cnt[14]\ : maxii_lcell
-- Equation(s):
-- cnt(14) = DFFEAS(cnt(14) $ (!(!\cnt[10]~115\ & \cnt[13]~113\) # (\cnt[10]~115\ & \cnt[13]~113COUT1_231\)), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[14]~131\ = CARRY(cnt(14) & (!\cnt[13]~113\))
-- \cnt[14]~131COUT1_233\ = CARRY(cnt(14) & (!\cnt[13]~113COUT1_231\))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "a50a",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(14),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[10]~115\,
	cin0 => \cnt[13]~113\,
	cin1 => \cnt[13]~113COUT1_231\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(14),
	cout0 => \cnt[14]~131\,
	cout1 => \cnt[14]~131COUT1_233\);

\cnt[15]\ : maxii_lcell
-- Equation(s):
-- cnt(15) = DFFEAS(cnt(15) $ (!\cnt[10]~115\ & \cnt[14]~131\) # (\cnt[10]~115\ & \cnt[14]~131COUT1_233\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[15]~133\ = CARRY(!\cnt[14]~131COUT1_233\ # !cnt(15))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => cnt(15),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[10]~115\,
	cin0 => \cnt[14]~131\,
	cin1 => \cnt[14]~131COUT1_233\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(15),
	cout => \cnt[15]~133\);

\cnt[16]\ : maxii_lcell
-- Equation(s):
-- cnt(16) = DFFEAS(cnt(16) $ !\cnt[15]~133\, GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[16]~135\ = CARRY(cnt(16) & !\cnt[15]~133\)
-- \cnt[16]~135COUT1_235\ = CARRY(cnt(16) & !\cnt[15]~133\)

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => cnt(16),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[15]~133\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(16),
	cout0 => \cnt[16]~135\,
	cout1 => \cnt[16]~135COUT1_235\);

\cnt[17]\ : maxii_lcell
-- Equation(s):
-- cnt(17) = DFFEAS(cnt(17) $ (!\cnt[15]~133\ & \cnt[16]~135\) # (\cnt[15]~133\ & \cnt[16]~135COUT1_235\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[17]~109\ = CARRY(!\cnt[16]~135\ # !cnt(17))
-- \cnt[17]~109COUT1_237\ = CARRY(!\cnt[16]~135COUT1_235\ # !cnt(17))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => cnt(17),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[15]~133\,
	cin0 => \cnt[16]~135\,
	cin1 => \cnt[16]~135COUT1_235\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(17),
	cout0 => \cnt[17]~109\,
	cout1 => \cnt[17]~109COUT1_237\);

\cnt[18]\ : maxii_lcell
-- Equation(s):
-- cnt(18) = DFFEAS(cnt(18) $ !(!\cnt[15]~133\ & \cnt[17]~109\) # (\cnt[15]~133\ & \cnt[17]~109COUT1_237\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[18]~111\ = CARRY(cnt(18) & !\cnt[17]~109\)
-- \cnt[18]~111COUT1_239\ = CARRY(cnt(18) & !\cnt[17]~109COUT1_237\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	datab => cnt(18),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[15]~133\,
	cin0 => \cnt[17]~109\,
	cin1 => \cnt[17]~109COUT1_237\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(18),
	cout0 => \cnt[18]~111\,
	cout1 => \cnt[18]~111COUT1_239\);

\cnt[19]\ : maxii_lcell
-- Equation(s):
-- cnt(19) = DFFEAS(cnt(19) $ ((!\cnt[15]~133\ & \cnt[18]~111\) # (\cnt[15]~133\ & \cnt[18]~111COUT1_239\)), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[19]~137\ = CARRY(!\cnt[18]~111\ # !cnt(19))
-- \cnt[19]~137COUT1_241\ = CARRY(!\cnt[18]~111COUT1_239\ # !cnt(19))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(19),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[15]~133\,
	cin0 => \cnt[18]~111\,
	cin1 => \cnt[18]~111COUT1_239\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(19),
	cout0 => \cnt[19]~137\,
	cout1 => \cnt[19]~137COUT1_241\);

\cnt[20]\ : maxii_lcell
-- Equation(s):
-- cnt(20) = DFFEAS(cnt(20) $ (!(!\cnt[15]~133\ & \cnt[19]~137\) # (\cnt[15]~133\ & \cnt[19]~137COUT1_241\)), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )
-- \cnt[20]~139\ = CARRY(cnt(20) & (!\cnt[19]~137COUT1_241\))

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "a50a",
	operation_mode => "arithmetic",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(20),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[15]~133\,
	cin0 => \cnt[19]~137\,
	cin1 => \cnt[19]~137COUT1_241\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(20),
	cout => \cnt[20]~139\);

\LessThan0~3\ : maxii_lcell
-- Equation(s):
-- \LessThan0~3_combout\ = cnt(14) # cnt(15) # cnt(16)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fffc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => cnt(14),
	datac => cnt(15),
	datad => cnt(16),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan0~3_combout\);

\LessThan0~0\ : maxii_lcell
-- Equation(s):
-- \LessThan0~0_combout\ = cnt(8) & cnt(7) & (cnt(6) # cnt(5))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c080",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => cnt(6),
	datab => cnt(8),
	datac => cnt(7),
	datad => cnt(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan0~0_combout\);

\LessThan0~1\ : maxii_lcell
-- Equation(s):
-- \LessThan0~1_combout\ = cnt(10) & (cnt(9) # \LessThan0~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ccc0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => cnt(10),
	datac => cnt(9),
	datad => \LessThan0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan0~1_combout\);

\LessThan0~2\ : maxii_lcell
-- Equation(s):
-- \LessThan0~2_combout\ = cnt(13) & (cnt(11) # cnt(12) # \LessThan0~1_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ccc8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => cnt(11),
	datab => cnt(13),
	datac => cnt(12),
	datad => \LessThan0~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan0~2_combout\);

\LessThan0~4\ : maxii_lcell
-- Equation(s):
-- \LessThan0~4_combout\ = cnt(17) & cnt(18) & (\LessThan0~3_combout\ # \LessThan0~2_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "8880",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => cnt(17),
	datab => cnt(18),
	datac => \LessThan0~3_combout\,
	datad => \LessThan0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan0~4_combout\);

\LessThan0~6\ : maxii_lcell
-- Equation(s):
-- \LessThan0~6_combout\ = cnt(21) & (cnt(19) # cnt(20) # \LessThan0~4_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aaa8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => cnt(21),
	datab => cnt(19),
	datac => cnt(20),
	datad => \LessThan0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan0~6_combout\);

\cnt[21]\ : maxii_lcell
-- Equation(s):
-- cnt(21) = DFFEAS(cnt(21) $ (\cnt[20]~139\), GLOBAL(\clk~combout\), !\Equal0~0_combout\, , , , , \LessThan0~6_combout\, )

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "5a5a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => cnt(21),
	aclr => \Equal0~0_combout\,
	sclr => \LessThan0~6_combout\,
	cin => \cnt[20]~139\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt(21));

\LessThan0~5\ : maxii_lcell
-- Equation(s):
-- \LessThan0~5_combout\ = cnt(20) # cnt(19)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fff0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => cnt(20),
	datad => cnt(19),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan0~5_combout\);

\key_temp0[2]~3\ : maxii_lcell
-- Equation(s):
-- \key_temp0[2]~3_combout\ = cnt(21) & !\Equal0~0_combout\ & (\LessThan0~5_combout\ # \LessThan0~4_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00a8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => cnt(21),
	datab => \LessThan0~5_combout\,
	datac => \LessThan0~4_combout\,
	datad => \Equal0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \key_temp0[2]~3_combout\);

\key_temp0[1]\ : maxii_lcell
-- Equation(s):
-- \process_4~1\ = key_temp0(2) & (key_temp0[1] & !key_temp0(0))
-- key_temp0(1) = DFFEAS(\process_4~1\, GLOBAL(\clk~combout\), VCC, , \key_temp0[2]~3_combout\, \ctrlin~combout\(1), , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00a0",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => key_temp0(2),
	datac => \ctrlin~combout\(1),
	datad => key_temp0(0),
	aclr => GND,
	sload => VCC,
	ena => \key_temp0[2]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \process_4~1\,
	regout => key_temp0(1));

\key_temp0[0]\ : maxii_lcell
-- Equation(s):
-- \Mux2~0\ = !key_temp0(2) & (key_temp0[0] & key_temp0(1))
-- key_temp0(0) = DFFEAS(\Mux2~0\, GLOBAL(\clk~combout\), VCC, , \key_temp0[2]~3_combout\, \ctrlin~combout\(0), , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5000",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => key_temp0(2),
	datac => \ctrlin~combout\(0),
	datad => key_temp0(1),
	aclr => GND,
	sload => VCC,
	ena => \key_temp0[2]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Mux2~0\,
	regout => key_temp0(0));

\sec1[1]\ : maxii_lcell
-- Equation(s):
-- sec1(1) = DFFEAS(!sec1(3) & (sec1(0) $ sec1(1)), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \process_4~1\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0330",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	datab => sec1(3),
	datac => sec1(0),
	datad => sec1(1),
	aclr => \Mux2~0\,
	ena => \process_4~1\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => sec1(1));

\sec1[0]\ : maxii_lcell
-- Equation(s):
-- sec1(0) = DFFEAS(!sec1(0) & (!sec1(2) & !sec1(1) # !sec1(3)), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \process_4~1\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0507",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	dataa => sec1(3),
	datab => sec1(2),
	datac => sec1(0),
	datad => sec1(1),
	aclr => \Mux2~0\,
	ena => \process_4~1\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => sec1(0));

\sec1[2]\ : maxii_lcell
-- Equation(s):
-- sec1(2) = DFFEAS(!sec1(3) & (sec1(2) $ (sec1(0) & sec1(1))), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \process_4~1\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1444",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	dataa => sec1(3),
	datab => sec1(2),
	datac => sec1(0),
	datad => sec1(1),
	aclr => \Mux2~0\,
	ena => \process_4~1\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => sec1(2));

\sec1[3]\ : maxii_lcell
-- Equation(s):
-- sec1(3) = DFFEAS(sec1(3) & !sec1(2) & !sec1(0) & !sec1(1) # !sec1(3) & sec1(2) & sec1(0) & sec1(1), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \process_4~1\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4002",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	dataa => sec1(3),
	datab => sec1(2),
	datac => sec1(0),
	datad => sec1(1),
	aclr => \Mux2~0\,
	ena => \process_4~1\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => sec1(3));

\LessThan5~0\ : maxii_lcell
-- Equation(s):
-- \LessThan5~0_combout\ = !sec1(1) & !sec1(2) & !sec1(0) # !sec1(3)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5557",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => sec1(3),
	datab => sec1(1),
	datac => sec1(2),
	datad => sec1(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan5~0_combout\);

\key_temp0[2]\ : maxii_lcell
-- Equation(s):
-- \sec10[3]~8\ = !key_temp0(0) & key_temp0(1) & key_temp0[2] & !\LessThan5~0_combout\
-- key_temp0(2) = DFFEAS(\sec10[3]~8\, GLOBAL(\clk~combout\), VCC, , \key_temp0[2]~3_combout\, \ctrlin~combout\(2), , , VCC)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0040",
	operation_mode => "normal",
	output_mode => "reg_and_comb",
	register_cascade_mode => "off",
	sum_lutc_input => "qfbk",
	synch_mode => "on")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => key_temp0(0),
	datab => key_temp0(1),
	datac => \ctrlin~combout\(2),
	datad => \LessThan5~0_combout\,
	aclr => GND,
	sload => VCC,
	ena => \key_temp0[2]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \sec10[3]~8\,
	regout => key_temp0(2));

\sec10[2]\ : maxii_lcell
-- Equation(s):
-- sec10(2) = DFFEAS(sec10(1) & !sec10(2) & sec10(0) # !sec10(1) & sec10(2) & !sec10(0), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \sec10[3]~8\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0c30",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	datab => sec10(1),
	datac => sec10(2),
	datad => sec10(0),
	aclr => \Mux2~0\,
	ena => \sec10[3]~8\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => sec10(2));

\sec10[1]\ : maxii_lcell
-- Equation(s):
-- sec10(1) = DFFEAS(!sec10(2) & (sec10(1) $ sec10(0)), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \sec10[3]~8\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "030c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	datab => sec10(1),
	datac => sec10(2),
	datad => sec10(0),
	aclr => \Mux2~0\,
	ena => \sec10[3]~8\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => sec10(1));

\sec10[0]\ : maxii_lcell
-- Equation(s):
-- sec10(0) = DFFEAS(!sec10(0) & (!sec10(2) # !sec10(1)), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \sec10[3]~8\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "003f",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	datab => sec10(1),
	datac => sec10(2),
	datad => sec10(0),
	aclr => \Mux2~0\,
	ena => \sec10[3]~8\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => sec10(0));

\min1[3]~13\ : maxii_lcell
-- Equation(s):
-- \min1[3]~13_combout\ = sec10(2) & \sec10[3]~8\ & (sec10(0) # sec10(1))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "e000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => sec10(0),
	datab => sec10(1),
	datac => sec10(2),
	datad => \sec10[3]~8\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \min1[3]~13_combout\);

\min1[2]\ : maxii_lcell
-- Equation(s):
-- min1(2) = DFFEAS(!min1(3) & (min1(2) $ (min1(0) & min1(1))), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \min1[3]~13_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1320",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	dataa => min1(0),
	datab => min1(3),
	datac => min1(1),
	datad => min1(2),
	aclr => \Mux2~0\,
	ena => \min1[3]~13_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => min1(2));

\min1[3]\ : maxii_lcell
-- Equation(s):
-- min1(3) = DFFEAS(min1(0) & !min1(3) & min1(1) & min1(2) # !min1(0) & min1(3) & !min1(1) & !min1(2), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \min1[3]~13_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "2004",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	dataa => min1(0),
	datab => min1(3),
	datac => min1(1),
	datad => min1(2),
	aclr => \Mux2~0\,
	ena => \min1[3]~13_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => min1(3));

\min1[0]\ : maxii_lcell
-- Equation(s):
-- min1(0) = DFFEAS(!min1(0) & (!min1(1) & !min1(2) # !min1(3)), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \min1[3]~13_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1115",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	dataa => min1(0),
	datab => min1(3),
	datac => min1(1),
	datad => min1(2),
	aclr => \Mux2~0\,
	ena => \min1[3]~13_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => min1(0));

\min1[1]\ : maxii_lcell
-- Equation(s):
-- min1(1) = DFFEAS(!min1(3) & (min1(0) $ min1(1)), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \min1[3]~13_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1212",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	dataa => min1(0),
	datab => min1(3),
	datac => min1(1),
	aclr => \Mux2~0\,
	ena => \min1[3]~13_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => min1(1));

\cnt2[0]\ : maxii_lcell
-- Equation(s):
-- cnt2(0) = DFFEAS(!cnt2(0), GLOBAL(\clk_1k~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00ff",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	datad => cnt2(0),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt2(0));

\cnt2[1]\ : maxii_lcell
-- Equation(s):
-- cnt2(1) = DFFEAS(cnt2(1) $ (cnt2(0)), GLOBAL(\clk_1k~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "55aa",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => cnt2(1),
	datad => cnt2(0),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt2(1));

\cnt2[2]\ : maxii_lcell
-- Equation(s):
-- cnt2(2) = DFFEAS(cnt2(2) & (!cnt2(1) # !cnt2(0)) # !cnt2(2) & cnt2(3) & cnt2(0) & cnt2(1), GLOBAL(\clk_1k~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "4aaa",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => cnt2(2),
	datab => cnt2(3),
	datac => cnt2(0),
	datad => cnt2(1),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt2(2));

\cnt2[3]\ : maxii_lcell
-- Equation(s):
-- cnt2(3) = DFFEAS(cnt2(3) $ (cnt2(2) & cnt2(1) & cnt2(0)), GLOBAL(\clk_1k~regout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "7f80",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => cnt2(2),
	datab => cnt2(1),
	datac => cnt2(0),
	datad => cnt2(3),
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => cnt2(3));

\data[3]~17\ : maxii_lcell
-- Equation(s):
-- \data[3]~17_combout\ = !cnt2(3) & !cnt2(2) & !cnt2(1)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0003",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => cnt2(3),
	datac => cnt2(2),
	datad => cnt2(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \data[3]~17_combout\);

\data[3]~18\ : maxii_lcell
-- Equation(s):
-- \data[3]~18_combout\ = !cnt2(3) & !cnt2(2) & !cnt2(0)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0003",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => cnt2(3),
	datac => cnt2(2),
	datad => cnt2(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \data[3]~18_combout\);

\data~21\ : maxii_lcell
-- Equation(s):
-- \data~21_combout\ = \data[3]~17_combout\ & (min1(1) # \data[3]~18_combout\) # !\data[3]~17_combout\ & (sec1(1) & !\data[3]~18_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f0ac",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => min1(1),
	datab => sec1(1),
	datac => \data[3]~17_combout\,
	datad => \data[3]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \data~21_combout\);

\LessThan7~0\ : maxii_lcell
-- Equation(s):
-- \LessThan7~0_combout\ = !min1(2) & !min1(1) & !min1(0) # !min1(3)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "01ff",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => min1(2),
	datab => min1(1),
	datac => min1(0),
	datad => min1(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan7~0_combout\);

\min10[3]~17\ : maxii_lcell
-- Equation(s):
-- \min10[3]~17_combout\ = !\LessThan7~0_combout\ & (\min1[3]~13_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "3300",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \LessThan7~0_combout\,
	datad => \min1[3]~13_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \min10[3]~17_combout\);

\min10[0]\ : maxii_lcell
-- Equation(s):
-- min10(0) = DFFEAS(!min10(0) & (!min10(1) # !min10(2)), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \min10[3]~17_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "003f",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	datab => min10(2),
	datac => min10(1),
	datad => min10(0),
	aclr => \Mux2~0\,
	ena => \min10[3]~17_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => min10(0));

\min10[2]\ : maxii_lcell
-- Equation(s):
-- min10(2) = DFFEAS(min10(2) & !min10(1) & !min10(0) # !min10(2) & min10(1) & min10(0), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \min10[3]~17_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "300c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	datab => min10(2),
	datac => min10(1),
	datad => min10(0),
	aclr => \Mux2~0\,
	ena => \min10[3]~17_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => min10(2));

\min10[1]\ : maxii_lcell
-- Equation(s):
-- min10(1) = DFFEAS(!min10(2) & (min10(1) $ min10(0)), GLOBAL(\timeclk~regout\), !\Mux2~0\, , \min10[3]~17_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0330",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \timeclk~regout\,
	datab => min10(2),
	datac => min10(1),
	datad => min10(0),
	aclr => \Mux2~0\,
	ena => \min10[3]~17_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => min10(1));

\data[3]~16\ : maxii_lcell
-- Equation(s):
-- \data[3]~16_combout\ = !cnt2(2) & !cnt2(3)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "000f",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => cnt2(2),
	datad => cnt2(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \data[3]~16_combout\);

\data[1]\ : maxii_lcell
-- Equation(s):
-- data(1) = DFFEAS(\data~21_combout\ & (min10(1) # !\data[3]~18_combout\) # !\data~21_combout\ & (sec10(1) & \data[3]~18_combout\), GLOBAL(\clk_1k~regout\), VCC, , \data[3]~16_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d8aa",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => \data~21_combout\,
	datab => min10(1),
	datac => sec10(1),
	datad => \data[3]~18_combout\,
	aclr => GND,
	ena => \data[3]~16_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data(1));

\data[3]\ : maxii_lcell
-- Equation(s):
-- data(3) = DFFEAS(!\data[3]~18_combout\ & (\data[3]~17_combout\ & (min1(3)) # !\data[3]~17_combout\ & sec1(3)), GLOBAL(\clk_1k~regout\), VCC, , \data[3]~16_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00ca",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => sec1(3),
	datab => min1(3),
	datac => \data[3]~17_combout\,
	datad => \data[3]~18_combout\,
	aclr => GND,
	ena => \data[3]~16_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data(3));

\data~23\ : maxii_lcell
-- Equation(s):
-- \data~23_combout\ = \data[3]~17_combout\ & (\data[3]~18_combout\) # !\data[3]~17_combout\ & (\data[3]~18_combout\ & (sec10(2)) # !\data[3]~18_combout\ & sec1(2))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fc22",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => sec1(2),
	datab => \data[3]~17_combout\,
	datac => sec10(2),
	datad => \data[3]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \data~23_combout\);

\data[2]\ : maxii_lcell
-- Equation(s):
-- data(2) = DFFEAS(\data[3]~17_combout\ & (\data~23_combout\ & min10(2) # !\data~23_combout\ & (min1(2))) # !\data[3]~17_combout\ & (\data~23_combout\), GLOBAL(\clk_1k~regout\), VCC, , \data[3]~16_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "dda0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => \data[3]~17_combout\,
	datab => min10(2),
	datac => min1(2),
	datad => \data~23_combout\,
	aclr => GND,
	ena => \data[3]~16_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data(2));

\data~19\ : maxii_lcell
-- Equation(s):
-- \data~19_combout\ = \data[3]~17_combout\ & (\data[3]~18_combout\) # !\data[3]~17_combout\ & (\data[3]~18_combout\ & (sec10(0)) # !\data[3]~18_combout\ & sec1(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fc0a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => sec1(0),
	datab => sec10(0),
	datac => \data[3]~17_combout\,
	datad => \data[3]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \data~19_combout\);

\data[0]\ : maxii_lcell
-- Equation(s):
-- data(0) = DFFEAS(\data[3]~17_combout\ & (\data~19_combout\ & min10(0) # !\data~19_combout\ & (min1(0))) # !\data[3]~17_combout\ & (\data~19_combout\), GLOBAL(\clk_1k~regout\), VCC, , \data[3]~16_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bbc0",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => min10(0),
	datab => \data[3]~17_combout\,
	datac => min1(0),
	datad => \data~19_combout\,
	aclr => GND,
	ena => \data[3]~16_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data(0));

\u|Mux7~0\ : maxii_lcell
-- Equation(s):
-- \u|Mux7~0_combout\ = data(3) & data(2) & (data(1) # data(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c080",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => data(1),
	datab => data(3),
	datac => data(2),
	datad => data(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|Mux7~0_combout\);

\u|Mux0~3\ : maxii_lcell
-- Equation(s):
-- \u|Mux0~3_combout\ = data(1) & data(3) # !data(1) & (data(2) $ (!data(3) & data(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ab98",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => data(3),
	datab => data(1),
	datac => data(0),
	datad => data(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|Mux0~3_combout\);

\u|dataout[0]\ : maxii_lcell
-- Equation(s):
-- \u|dataout\(0) = GLOBAL(\u|Mux7~0_combout\) & (\u|dataout\(0)) # !GLOBAL(\u|Mux7~0_combout\) & !\u|Mux0~3_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cf03",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \u|Mux7~0_combout\,
	datac => \u|Mux0~3_combout\,
	datad => \u|dataout\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|dataout\(0));

\u|Mux1~3\ : maxii_lcell
-- Equation(s):
-- \u|Mux1~3_combout\ = data(3) & (data(1) # data(2)) # !data(3) & data(2) & (data(1) $ data(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "be88",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => data(3),
	datab => data(1),
	datac => data(0),
	datad => data(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|Mux1~3_combout\);

\u|dataout[1]\ : maxii_lcell
-- Equation(s):
-- \u|dataout\(1) = GLOBAL(\u|Mux7~0_combout\) & (\u|dataout\(1)) # !GLOBAL(\u|Mux7~0_combout\) & !\u|Mux1~3_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cf03",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \u|Mux7~0_combout\,
	datac => \u|Mux1~3_combout\,
	datad => \u|dataout\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|dataout\(1));

\u|Mux2~3\ : maxii_lcell
-- Equation(s):
-- \u|Mux2~3_combout\ = data(2) & data(3) # !data(2) & data(1) & (data(3) # !data(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa8c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => data(3),
	datab => data(1),
	datac => data(0),
	datad => data(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|Mux2~3_combout\);

\u|dataout[2]\ : maxii_lcell
-- Equation(s):
-- \u|dataout\(2) = GLOBAL(\u|Mux7~0_combout\) & (\u|dataout\(2)) # !GLOBAL(\u|Mux7~0_combout\) & !\u|Mux2~3_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f033",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \u|Mux2~3_combout\,
	datac => \u|dataout\(2),
	datad => \u|Mux7~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|dataout\(2));

\u|Mux3~3\ : maxii_lcell
-- Equation(s):
-- \u|Mux3~3_combout\ = data(1) & (data(3) # data(0) & data(2)) # !data(1) & (data(2) $ (!data(3) & data(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "eb98",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => data(3),
	datab => data(1),
	datac => data(0),
	datad => data(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|Mux3~3_combout\);

\u|dataout[3]\ : maxii_lcell
-- Equation(s):
-- \u|dataout\(3) = GLOBAL(\u|Mux7~0_combout\) & (\u|dataout\(3)) # !GLOBAL(\u|Mux7~0_combout\) & !\u|Mux3~3_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cf03",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \u|Mux7~0_combout\,
	datac => \u|Mux3~3_combout\,
	datad => \u|dataout\(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|dataout\(3));

\u|Mux4~3\ : maxii_lcell
-- Equation(s):
-- \u|Mux4~3_combout\ = data(0) # data(1) & data(3) # !data(1) & (data(2))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fbf8",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => data(3),
	datab => data(1),
	datac => data(0),
	datad => data(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|Mux4~3_combout\);

\u|dataout[4]\ : maxii_lcell
-- Equation(s):
-- \u|dataout\(4) = GLOBAL(\u|Mux7~0_combout\) & (\u|dataout\(4)) # !GLOBAL(\u|Mux7~0_combout\) & !\u|Mux4~3_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f033",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \u|Mux4~3_combout\,
	datac => \u|dataout\(4),
	datad => \u|Mux7~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|dataout\(4));

\u|Mux5~3\ : maxii_lcell
-- Equation(s):
-- \u|Mux5~3_combout\ = data(0) & (data(1) # data(3) $ !data(2)) # !data(0) & (data(2) & data(3) # !data(2) & (data(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "eadc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => data(3),
	datab => data(1),
	datac => data(0),
	datad => data(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|Mux5~3_combout\);

\u|dataout[5]\ : maxii_lcell
-- Equation(s):
-- \u|dataout\(5) = GLOBAL(\u|Mux7~0_combout\) & (\u|dataout\(5)) # !GLOBAL(\u|Mux7~0_combout\) & !\u|Mux5~3_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cf03",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \u|Mux7~0_combout\,
	datac => \u|Mux5~3_combout\,
	datad => \u|dataout\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|dataout\(5));

\u|Mux6~3\ : maxii_lcell
-- Equation(s):
-- \u|Mux6~3_combout\ = data(3) & (!data(2)) # !data(3) & (data(1) & (!data(2) # !data(0)) # !data(1) & (data(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "15ee",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => data(3),
	datab => data(1),
	datac => data(0),
	datad => data(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|Mux6~3_combout\);

\u|dataout[6]\ : maxii_lcell
-- Equation(s):
-- \u|dataout\(6) = GLOBAL(\u|Mux7~0_combout\) & (\u|dataout\(6)) # !GLOBAL(\u|Mux7~0_combout\) & \u|Mux6~3_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f0aa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \u|Mux6~3_combout\,
	datac => \u|dataout\(6),
	datad => \u|Mux7~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \u|dataout\(6));

\CLK_1Khz:cnt[8]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[8]~regout\ = DFFEAS(\Add1~18_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f070",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~22_combout\,
	datab => \Add1~24_combout\,
	datac => \Add1~18_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[8]~regout\);

\Add1~30\ : maxii_lcell
-- Equation(s):
-- \Add1~30_combout\ = !\CLK_1Khz:cnt[0]~regout\
-- \Add1~31\ = CARRY(\CLK_1Khz:cnt[0]~regout\)
-- \Add1~31COUT1_46\ = CARRY(\CLK_1Khz:cnt[0]~regout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "33cc",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[0]~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~30_combout\,
	cout0 => \Add1~31\,
	cout1 => \Add1~31COUT1_46\);

\CLK_1Khz:cnt[0]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[0]~regout\ = DFFEAS(\Add1~30_combout\ & (\LessThan2~2_combout\ # !\Add1~22_combout\ # !\Add1~24_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f070",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~24_combout\,
	datab => \Add1~22_combout\,
	datac => \Add1~30_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[0]~regout\);

\Add1~28\ : maxii_lcell
-- Equation(s):
-- \Add1~28_combout\ = \CLK_1Khz:cnt[1]~regout\ $ (\Add1~31\)
-- \Add1~29\ = CARRY(!\Add1~31\ # !\CLK_1Khz:cnt[1]~regout\)
-- \Add1~29COUT1_48\ = CARRY(!\Add1~31COUT1_46\ # !\CLK_1Khz:cnt[1]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \CLK_1Khz:cnt[1]~regout\,
	cin0 => \Add1~31\,
	cin1 => \Add1~31COUT1_46\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~28_combout\,
	cout0 => \Add1~29\,
	cout1 => \Add1~29COUT1_48\);

\CLK_1Khz:cnt[1]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[1]~regout\ = DFFEAS(\Add1~28_combout\ & (\LessThan2~2_combout\ # !\Add1~22_combout\ # !\Add1~24_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "a2aa",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~28_combout\,
	datab => \Add1~24_combout\,
	datac => \LessThan2~2_combout\,
	datad => \Add1~22_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[1]~regout\);

\Add1~26\ : maxii_lcell
-- Equation(s):
-- \Add1~26_combout\ = \CLK_1Khz:cnt[2]~regout\ $ !\Add1~29\
-- \Add1~27\ = CARRY(\CLK_1Khz:cnt[2]~regout\ & !\Add1~29COUT1_48\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[2]~regout\,
	cin0 => \Add1~29\,
	cin1 => \Add1~29COUT1_48\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~26_combout\,
	cout => \Add1~27\);

\CLK_1Khz:cnt[2]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[2]~regout\ = DFFEAS(\Add1~26_combout\ & (\LessThan2~2_combout\ # !\Add1~22_combout\ # !\Add1~24_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc4c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~24_combout\,
	datab => \Add1~26_combout\,
	datac => \Add1~22_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[2]~regout\);

\Add1~8\ : maxii_lcell
-- Equation(s):
-- \Add1~8_combout\ = \CLK_1Khz:cnt[3]~regout\ $ \Add1~27\
-- \Add1~9\ = CARRY(!\Add1~27\ # !\CLK_1Khz:cnt[3]~regout\)
-- \Add1~9COUT1_50\ = CARRY(!\Add1~27\ # !\CLK_1Khz:cnt[3]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[3]~regout\,
	cin => \Add1~27\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~8_combout\,
	cout0 => \Add1~9\,
	cout1 => \Add1~9COUT1_50\);

\CLK_1Khz:cnt[3]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[3]~regout\ = DFFEAS(\Add1~8_combout\ & (\LessThan2~2_combout\ # !\Add1~22_combout\ # !\Add1~24_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc4c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~24_combout\,
	datab => \Add1~8_combout\,
	datac => \Add1~22_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[3]~regout\);

\Add1~10\ : maxii_lcell
-- Equation(s):
-- \Add1~10_combout\ = \CLK_1Khz:cnt[4]~regout\ $ !(!\Add1~27\ & \Add1~9\) # (\Add1~27\ & \Add1~9COUT1_50\)
-- \Add1~11\ = CARRY(\CLK_1Khz:cnt[4]~regout\ & !\Add1~9\)
-- \Add1~11COUT1_52\ = CARRY(\CLK_1Khz:cnt[4]~regout\ & !\Add1~9COUT1_50\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[4]~regout\,
	cin => \Add1~27\,
	cin0 => \Add1~9\,
	cin1 => \Add1~9COUT1_50\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~10_combout\,
	cout0 => \Add1~11\,
	cout1 => \Add1~11COUT1_52\);

\CLK_1Khz:cnt[4]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[4]~regout\ = DFFEAS(\Add1~10_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa2a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~10_combout\,
	datab => \Add1~22_combout\,
	datac => \Add1~24_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[4]~regout\);

\Add1~12\ : maxii_lcell
-- Equation(s):
-- \Add1~12_combout\ = \CLK_1Khz:cnt[5]~regout\ $ ((!\Add1~27\ & \Add1~11\) # (\Add1~27\ & \Add1~11COUT1_52\))
-- \Add1~13\ = CARRY(!\Add1~11\ # !\CLK_1Khz:cnt[5]~regout\)
-- \Add1~13COUT1_54\ = CARRY(!\Add1~11COUT1_52\ # !\CLK_1Khz:cnt[5]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \CLK_1Khz:cnt[5]~regout\,
	cin => \Add1~27\,
	cin0 => \Add1~11\,
	cin1 => \Add1~11COUT1_52\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~12_combout\,
	cout0 => \Add1~13\,
	cout1 => \Add1~13COUT1_54\);

\CLK_1Khz:cnt[5]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[5]~regout\ = DFFEAS(\Add1~12_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa2a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~12_combout\,
	datab => \Add1~22_combout\,
	datac => \Add1~24_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[5]~regout\);

\Add1~14\ : maxii_lcell
-- Equation(s):
-- \Add1~14_combout\ = \CLK_1Khz:cnt[6]~regout\ $ !(!\Add1~27\ & \Add1~13\) # (\Add1~27\ & \Add1~13COUT1_54\)
-- \Add1~15\ = CARRY(\CLK_1Khz:cnt[6]~regout\ & !\Add1~13\)
-- \Add1~15COUT1_56\ = CARRY(\CLK_1Khz:cnt[6]~regout\ & !\Add1~13COUT1_54\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[6]~regout\,
	cin => \Add1~27\,
	cin0 => \Add1~13\,
	cin1 => \Add1~13COUT1_54\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~14_combout\,
	cout0 => \Add1~15\,
	cout1 => \Add1~15COUT1_56\);

\CLK_1Khz:cnt[6]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[6]~regout\ = DFFEAS(\Add1~14_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc4c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~22_combout\,
	datab => \Add1~14_combout\,
	datac => \Add1~24_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[6]~regout\);

\Add1~16\ : maxii_lcell
-- Equation(s):
-- \Add1~16_combout\ = \CLK_1Khz:cnt[7]~regout\ $ (!\Add1~27\ & \Add1~15\) # (\Add1~27\ & \Add1~15COUT1_56\)
-- \Add1~17\ = CARRY(!\Add1~15COUT1_56\ # !\CLK_1Khz:cnt[7]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[7]~regout\,
	cin => \Add1~27\,
	cin0 => \Add1~15\,
	cin1 => \Add1~15COUT1_56\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~16_combout\,
	cout => \Add1~17\);

\CLK_1Khz:cnt[7]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[7]~regout\ = DFFEAS(\Add1~16_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc4c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~22_combout\,
	datab => \Add1~16_combout\,
	datac => \Add1~24_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[7]~regout\);

\Add1~18\ : maxii_lcell
-- Equation(s):
-- \Add1~18_combout\ = \CLK_1Khz:cnt[8]~regout\ $ !\Add1~17\
-- \Add1~19\ = CARRY(\CLK_1Khz:cnt[8]~regout\ & !\Add1~17\)
-- \Add1~19COUT1_58\ = CARRY(\CLK_1Khz:cnt[8]~regout\ & !\Add1~17\)

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[8]~regout\,
	cin => \Add1~17\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~18_combout\,
	cout0 => \Add1~19\,
	cout1 => \Add1~19COUT1_58\);

\CLK_1Khz:cnt[9]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[9]~regout\ = DFFEAS(\Add1~0_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc4c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~22_combout\,
	datab => \Add1~0_combout\,
	datac => \Add1~24_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[9]~regout\);

\Add1~0\ : maxii_lcell
-- Equation(s):
-- \Add1~0_combout\ = \CLK_1Khz:cnt[9]~regout\ $ ((!\Add1~17\ & \Add1~19\) # (\Add1~17\ & \Add1~19COUT1_58\))
-- \Add1~1\ = CARRY(!\Add1~19\ # !\CLK_1Khz:cnt[9]~regout\)
-- \Add1~1COUT1_60\ = CARRY(!\Add1~19COUT1_58\ # !\CLK_1Khz:cnt[9]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "5a5f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \CLK_1Khz:cnt[9]~regout\,
	cin => \Add1~17\,
	cin0 => \Add1~19\,
	cin1 => \Add1~19COUT1_58\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~0_combout\,
	cout0 => \Add1~1\,
	cout1 => \Add1~1COUT1_60\);

\LessThan2~1\ : maxii_lcell
-- Equation(s):
-- \LessThan2~1_combout\ = !\Add1~16_combout\ & (!\Add1~10_combout\ & !\Add1~12_combout\ # !\Add1~14_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0307",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add1~10_combout\,
	datab => \Add1~14_combout\,
	datac => \Add1~16_combout\,
	datad => \Add1~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan2~1_combout\);

\CLK_1Khz:cnt[10]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[10]~regout\ = DFFEAS(\Add1~2_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa2a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~2_combout\,
	datab => \Add1~22_combout\,
	datac => \Add1~24_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[10]~regout\);

\Add1~2\ : maxii_lcell
-- Equation(s):
-- \Add1~2_combout\ = \CLK_1Khz:cnt[10]~regout\ $ !(!\Add1~17\ & \Add1~1\) # (\Add1~17\ & \Add1~1COUT1_60\)
-- \Add1~3\ = CARRY(\CLK_1Khz:cnt[10]~regout\ & !\Add1~1\)
-- \Add1~3COUT1_62\ = CARRY(\CLK_1Khz:cnt[10]~regout\ & !\Add1~1COUT1_60\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[10]~regout\,
	cin => \Add1~17\,
	cin0 => \Add1~1\,
	cin1 => \Add1~1COUT1_60\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~2_combout\,
	cout0 => \Add1~3\,
	cout1 => \Add1~3COUT1_62\);

\CLK_1Khz:cnt[11]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[11]~regout\ = DFFEAS(\Add1~4_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc4c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~22_combout\,
	datab => \Add1~4_combout\,
	datac => \Add1~24_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[11]~regout\);

\Add1~4\ : maxii_lcell
-- Equation(s):
-- \Add1~4_combout\ = \CLK_1Khz:cnt[11]~regout\ $ (!\Add1~17\ & \Add1~3\) # (\Add1~17\ & \Add1~3COUT1_62\)
-- \Add1~5\ = CARRY(!\Add1~3\ # !\CLK_1Khz:cnt[11]~regout\)
-- \Add1~5COUT1_64\ = CARRY(!\Add1~3COUT1_62\ # !\CLK_1Khz:cnt[11]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[11]~regout\,
	cin => \Add1~17\,
	cin0 => \Add1~3\,
	cin1 => \Add1~3COUT1_62\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~4_combout\,
	cout0 => \Add1~5\,
	cout1 => \Add1~5COUT1_64\);

\CLK_1Khz:cnt[12]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[12]~regout\ = DFFEAS(\Add1~6_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa2a",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~6_combout\,
	datab => \Add1~22_combout\,
	datac => \Add1~24_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[12]~regout\);

\Add1~6\ : maxii_lcell
-- Equation(s):
-- \Add1~6_combout\ = \CLK_1Khz:cnt[12]~regout\ $ !(!\Add1~17\ & \Add1~5\) # (\Add1~17\ & \Add1~5COUT1_64\)
-- \Add1~7\ = CARRY(\CLK_1Khz:cnt[12]~regout\ & !\Add1~5COUT1_64\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[12]~regout\,
	cin => \Add1~17\,
	cin0 => \Add1~5\,
	cin1 => \Add1~5COUT1_64\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~6_combout\,
	cout => \Add1~7\);

\CLK_1Khz:cnt[13]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[13]~regout\ = DFFEAS(\Add1~20_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc4c",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~22_combout\,
	datab => \Add1~20_combout\,
	datac => \Add1~24_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[13]~regout\);

\Add1~20\ : maxii_lcell
-- Equation(s):
-- \Add1~20_combout\ = \CLK_1Khz:cnt[13]~regout\ $ \Add1~7\
-- \Add1~21\ = CARRY(!\Add1~7\ # !\CLK_1Khz:cnt[13]~regout\)
-- \Add1~21COUT1_66\ = CARRY(!\Add1~7\ # !\CLK_1Khz:cnt[13]~regout\)

-- pragma translate_off
GENERIC MAP (
	cin_used => "true",
	lut_mask => "3c3f",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[13]~regout\,
	cin => \Add1~7\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~20_combout\,
	cout0 => \Add1~21\,
	cout1 => \Add1~21COUT1_66\);

\LessThan2~0\ : maxii_lcell
-- Equation(s):
-- \LessThan2~0_combout\ = !\Add1~2_combout\ & !\Add1~4_combout\ & !\Add1~6_combout\ & !\Add1~20_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add1~2_combout\,
	datab => \Add1~4_combout\,
	datac => \Add1~6_combout\,
	datad => \Add1~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan2~0_combout\);

\LessThan2~2\ : maxii_lcell
-- Equation(s):
-- \LessThan2~2_combout\ = \LessThan2~0_combout\ & (\LessThan2~1_combout\ # !\Add1~0_combout\ # !\Add1~18_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f700",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add1~18_combout\,
	datab => \Add1~0_combout\,
	datac => \LessThan2~1_combout\,
	datad => \LessThan2~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan2~2_combout\);

\CLK_1Khz:cnt[14]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[14]~regout\ = DFFEAS(\Add1~22_combout\ & (\LessThan2~2_combout\ # !\Add1~24_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc44",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~24_combout\,
	datab => \Add1~22_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[14]~regout\);

\Add1~22\ : maxii_lcell
-- Equation(s):
-- \Add1~22_combout\ = \CLK_1Khz:cnt[14]~regout\ $ !(!\Add1~7\ & \Add1~21\) # (\Add1~7\ & \Add1~21COUT1_66\)
-- \Add1~23\ = CARRY(\CLK_1Khz:cnt[14]~regout\ & !\Add1~21\)
-- \Add1~23COUT1_68\ = CARRY(\CLK_1Khz:cnt[14]~regout\ & !\Add1~21COUT1_66\)

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "c30c",
	operation_mode => "arithmetic",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \CLK_1Khz:cnt[14]~regout\,
	cin => \Add1~7\,
	cin0 => \Add1~21\,
	cin1 => \Add1~21COUT1_66\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~22_combout\,
	cout0 => \Add1~23\,
	cout1 => \Add1~23COUT1_68\);

\CLK_1Khz:cnt[15]\ : maxii_lcell
-- Equation(s):
-- \CLK_1Khz:cnt[15]~regout\ = DFFEAS(\Add1~24_combout\ & (\LessThan2~2_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa22",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~24_combout\,
	datab => \Add1~22_combout\,
	datad => \LessThan2~2_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \CLK_1Khz:cnt[15]~regout\);

\Add1~24\ : maxii_lcell
-- Equation(s):
-- \Add1~24_combout\ = (!\Add1~7\ & \Add1~23\) # (\Add1~7\ & \Add1~23COUT1_68\) $ \CLK_1Khz:cnt[15]~regout\

-- pragma translate_off
GENERIC MAP (
	cin0_used => "true",
	cin1_used => "true",
	cin_used => "true",
	lut_mask => "0ff0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "cin",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datad => \CLK_1Khz:cnt[15]~regout\,
	cin => \Add1~7\,
	cin0 => \Add1~23\,
	cin1 => \Add1~23COUT1_68\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \Add1~24_combout\);

\LessThan1~1\ : maxii_lcell
-- Equation(s):
-- \LessThan1~1_combout\ = !\Add1~14_combout\ & (!\Add1~8_combout\ & !\Add1~10_combout\ # !\Add1~12_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "010f",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add1~8_combout\,
	datab => \Add1~10_combout\,
	datac => \Add1~14_combout\,
	datad => \Add1~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan1~1_combout\);

\LessThan1~0\ : maxii_lcell
-- Equation(s):
-- \LessThan1~0_combout\ = !\Add1~6_combout\ & !\Add1~4_combout\ & !\Add1~0_combout\ & !\Add1~2_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add1~6_combout\,
	datab => \Add1~4_combout\,
	datac => \Add1~0_combout\,
	datad => \Add1~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan1~0_combout\);

\LessThan1~2\ : maxii_lcell
-- Equation(s):
-- \LessThan1~2_combout\ = \LessThan1~0_combout\ & (\LessThan1~1_combout\ # !\Add1~18_combout\ # !\Add1~16_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "df00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \Add1~16_combout\,
	datab => \LessThan1~1_combout\,
	datac => \Add1~18_combout\,
	datad => \LessThan1~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \LessThan1~2_combout\);

clk_1k : maxii_lcell
-- Equation(s):
-- \clk_1k~regout\ = DFFEAS(!\Add1~24_combout\ & (\LessThan1~2_combout\ # !\Add1~20_combout\ # !\Add1~22_combout\), GLOBAL(\clk~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "5155",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk~combout\,
	dataa => \Add1~24_combout\,
	datab => \Add1~22_combout\,
	datac => \LessThan1~2_combout\,
	datad => \Add1~20_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \clk_1k~regout\);

\ledcs[0]~reg0\ : maxii_lcell
-- Equation(s):
-- \ledcs[0]~reg0_regout\ = DFFEAS(!cnt2(2) & !cnt2(3) & (!cnt2(0) # !cnt2(1)), GLOBAL(\clk_1k~regout\), VCC, , \data[3]~16_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0015",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => cnt2(2),
	datab => cnt2(1),
	datac => cnt2(0),
	datad => cnt2(3),
	aclr => GND,
	ena => \data[3]~16_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \ledcs[0]~reg0_regout\);

\ledcs[1]~reg0\ : maxii_lcell
-- Equation(s):
-- \ledcs[1]~reg0_regout\ = DFFEAS(cnt2(2) # cnt2(0) # cnt2(3) # !cnt2(1), GLOBAL(\clk_1k~regout\), VCC, , \data[3]~16_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fffb",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => cnt2(2),
	datab => cnt2(1),
	datac => cnt2(0),
	datad => cnt2(3),
	aclr => GND,
	ena => \data[3]~16_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \ledcs[1]~reg0_regout\);

\ledcs[2]~reg0\ : maxii_lcell
-- Equation(s):
-- \ledcs[2]~reg0_regout\ = DFFEAS(cnt2(2) # cnt2(1) # cnt2(3) # !cnt2(0), GLOBAL(\clk_1k~regout\), VCC, , \data[3]~16_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ffef",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => cnt2(2),
	datab => cnt2(1),
	datac => cnt2(0),
	datad => cnt2(3),
	aclr => GND,
	ena => \data[3]~16_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \ledcs[2]~reg0_regout\);

\ledcs[3]~reg0\ : maxii_lcell
-- Equation(s):
-- \ledcs[3]~reg0_regout\ = DFFEAS(cnt2(2) # cnt2(1) # cnt2(0) # cnt2(3), GLOBAL(\clk_1k~regout\), VCC, , \data[3]~16_combout\, , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fffe",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \clk_1k~regout\,
	dataa => cnt2(2),
	datab => cnt2(1),
	datac => cnt2(0),
	datad => cnt2(3),
	aclr => GND,
	ena => \data[3]~16_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \ledcs[3]~reg0_regout\);

\disp[0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \u|dataout\(0),
	oe => VCC,
	padio => ww_disp(0));

\disp[1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \u|dataout\(1),
	oe => VCC,
	padio => ww_disp(1));

\disp[2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \u|dataout\(2),
	oe => VCC,
	padio => ww_disp(2));

\disp[3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \u|dataout\(3),
	oe => VCC,
	padio => ww_disp(3));

\disp[4]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \u|dataout\(4),
	oe => VCC,
	padio => ww_disp(4));

\disp[5]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \u|dataout\(5),
	oe => VCC,
	padio => ww_disp(5));

\disp[6]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \u|dataout\(6),
	oe => VCC,
	padio => ww_disp(6));

\disp[7]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_disp(7));

\ledcs[0]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \ledcs[0]~reg0_regout\,
	oe => VCC,
	padio => ww_ledcs(0));

\ledcs[1]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \ledcs[1]~reg0_regout\,
	oe => VCC,
	padio => ww_ledcs(1));

\ledcs[2]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \ledcs[2]~reg0_regout\,
	oe => VCC,
	padio => ww_ledcs(2));

\ledcs[3]~I\ : maxii_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \ledcs[3]~reg0_regout\,
	oe => VCC,
	padio => ww_ledcs(3));
END structure;


