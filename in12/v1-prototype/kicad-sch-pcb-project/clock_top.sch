EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L custom_library:MAX1771 D1
U 1 1 5E080E15
P 5100 8450
F 0 "D1" H 5450 8900 50  0000 C CNN
F 1 "MAX1771" H 5750 7950 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5450 9000 50  0001 C CNN
F 3 "" H 5450 9000 50  0001 C CNN
	1    5100 8450
	1    0    0    -1  
$EndComp
$Comp
L custom_library:STD18N55M5 VT1
U 1 1 5E085881
P 6450 8250
F 0 "VT1" H 6300 8500 50  0000 L CNN
F 1 "STD18N55M5" H 6300 8400 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-252-2" H 6350 8100 50  0001 C CNN
F 3 "https://www.st.com/resource/en/datasheet/std18n55m5.pdf" H 6350 8100 50  0001 C CNN
	1    6450 8250
	1    0    0    -1  
$EndComp
$Comp
L custom_library:ES2J VD1
U 1 1 5E08A288
P 6550 7800
F 0 "VD1" H 6600 7484 50  0000 C CNN
F 1 "ES2J" H 6600 7575 50  0000 C CNN
F 2 "Diode_SMD:D_SMB_Handsoldering" H 6550 7800 50  0001 C CNN
F 3 "https://www.taiwansemi.com/products/datasheet/ES2A%20SERIES_K1701.pdf" H 6550 7800 50  0001 C CNN
	1    6550 7800
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 8250 5800 8250
$Comp
L custom_library:B82477R4224M100 L1
U 1 1 5E09A95A
P 6000 7700
F 0 "L1" V 6195 7700 50  0000 C CNN
F 1 "B82477R4224M100" V 6104 7700 50  0000 C CNN
F 2 "Inductor_SMD:L_12x12mm_H8mm" H 6000 7700 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2137660.pdf" H 6000 7700 50  0001 C CNN
	1    6000 7700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5800 8500 6250 8500
Wire Wire Line
	6250 8500 6250 8450
$Comp
L Device:R R4
U 1 1 5E0A23CF
P 6250 8700
F 0 "R4" H 6320 8746 50  0000 L CNN
F 1 "0.1" H 6320 8655 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 6180 8700 50  0001 C CNN
F 3 "~" H 6250 8700 50  0001 C CNN
	1    6250 8700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 8500 6250 8550
Connection ~ 6250 8500
Wire Wire Line
	6250 9300 5550 9300
Wire Wire Line
	6250 8850 6250 9300
Wire Wire Line
	5450 9000 5450 9300
Connection ~ 5450 9300
Wire Wire Line
	5450 9300 5250 9300
Wire Wire Line
	5550 9000 5550 9300
Connection ~ 5550 9300
Wire Wire Line
	5550 9300 5450 9300
$Comp
L power:GND #PWR0101
U 1 1 5E0A583A
P 5250 9400
F 0 "#PWR0101" H 5250 9150 50  0001 C CNN
F 1 "GND" H 5255 9227 50  0000 C CNN
F 2 "" H 5250 9400 50  0001 C CNN
F 3 "" H 5250 9400 50  0001 C CNN
	1    5250 9400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 9300 5250 9400
Connection ~ 5250 9300
$Comp
L Device:C C3
U 1 1 5E0A452F
P 5250 9150
F 0 "C3" H 5050 9200 50  0000 L CNN
F 1 "100nF" H 4900 9100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5288 9000 50  0001 C CNN
F 3 "~" H 5250 9150 50  0001 C CNN
	1    5250 9150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5E0A94F2
P 7150 8550
F 0 "C5" H 7200 8650 50  0000 L CNN
F 1 "100nF, 250V" V 7350 8600 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7188 8400 50  0001 C CNN
F 3 "~" H 7150 8550 50  0001 C CNN
	1    7150 8550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 5E0A6EBB
P 6850 8550
F 0 "C4" H 6950 8650 50  0000 R CNN
F 1 "10 uF, 250V" V 7000 9100 50  0000 R CNN
F 2 "Capacitor_THT:C_Axial_L22.0mm_D10.5mm_P27.50mm_Horizontal" H 6888 8400 50  0001 C CNN
F 3 "~" H 6850 8550 50  0001 C CNN
	1    6850 8550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 8700 6850 9300
Wire Wire Line
	6850 9300 6250 9300
Connection ~ 6250 9300
Wire Wire Line
	7150 8700 7150 9300
Wire Wire Line
	7150 9300 6850 9300
Connection ~ 6850 9300
$Comp
L Device:R R6
U 1 1 5E0B609C
P 7550 8200
F 0 "R6" H 7620 8246 50  0000 L CNN
F 1 "1.5M" H 7620 8155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7480 8200 50  0001 C CNN
F 3 "~" H 7550 8200 50  0001 C CNN
	1    7550 8200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 5E0B9216
P 7550 9150
F 0 "RV1" H 7481 9196 50  0000 R CNN
F 1 "R_POT" H 7481 9105 50  0000 R CNN
F 2 "clock:3296W" H 7550 9150 50  0001 C CNN
F 3 "https://static.chipdip.ru/lib/237/DOC000237859.pdf" H 7550 9150 50  0001 C CNN
	1    7550 9150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 8700 7550 8500
Wire Wire Line
	7550 8500 7400 8500
Wire Wire Line
	7400 8950 5950 8950
Wire Wire Line
	5950 8950 5950 8700
Wire Wire Line
	5950 8700 5800 8700
Connection ~ 7550 8500
Wire Wire Line
	7550 8500 7550 8350
Wire Wire Line
	7550 9300 7150 9300
Connection ~ 7150 9300
Wire Wire Line
	7700 9150 7700 9300
Wire Wire Line
	7700 9300 7550 9300
Connection ~ 7550 9300
Wire Wire Line
	6250 7700 6350 7700
Wire Wire Line
	6250 7700 6250 8050
Wire Wire Line
	6250 7700 6150 7700
Connection ~ 6250 7700
Wire Wire Line
	6650 7700 6850 7700
Wire Wire Line
	6850 7700 6850 8400
Wire Wire Line
	6850 7700 7150 7700
Wire Wire Line
	7150 7700 7150 8400
Connection ~ 6850 7700
Wire Wire Line
	7150 7700 7400 7700
Wire Wire Line
	7550 7700 7550 8050
Connection ~ 7150 7700
Wire Wire Line
	5850 7700 5350 7700
Wire Wire Line
	5350 7700 5350 7950
$Comp
L custom_library:IN-12B LL2
U 1 1 5E0D0AD1
P 14350 2850
F 0 "LL2" H 14375 3315 50  0000 C CNN
F 1 "IN-12B" H 14375 3224 50  0000 C CNN
F 2 "clock:PL31" H 14350 3200 50  0001 C CNN
F 3 "https://istok2.com/data/1719/" H 14350 3200 50  0001 C CNN
	1    14350 2850
	1    0    0    -1  
$EndComp
Wire Bus Line
	13800 3750 12850 3750
Connection ~ 12850 3750
Text Label 11150 1800 0    50   ~ 0
1-0
Wire Wire Line
	12750 1500 12500 1500
Wire Wire Line
	12750 1600 12500 1600
Wire Wire Line
	12750 1700 12500 1700
Wire Wire Line
	12750 1800 12500 1800
Wire Wire Line
	12750 1900 12500 1900
Wire Wire Line
	12750 2000 12500 2000
Wire Wire Line
	12750 2100 12500 2100
Wire Wire Line
	12750 2200 12500 2200
Wire Wire Line
	12750 2300 12500 2300
Wire Wire Line
	12750 2400 12500 2400
Wire Bus Line
	11000 3750 12850 3750
Wire Wire Line
	11400 1500 11100 1500
Wire Wire Line
	11400 1600 11100 1600
Wire Wire Line
	11400 1800 11100 1800
Wire Wire Line
	11100 1900 11400 1900
Wire Wire Line
	11400 2000 11100 2000
Wire Wire Line
	11100 2200 11400 2200
Entry Wire Line
	12750 1500 12850 1600
Entry Wire Line
	12750 1600 12850 1700
Entry Wire Line
	12750 1700 12850 1800
Entry Wire Line
	12750 1800 12850 1900
Entry Wire Line
	12750 1900 12850 2000
Entry Wire Line
	12750 2000 12850 2100
Entry Wire Line
	12750 2100 12850 2200
Entry Wire Line
	12750 2200 12850 2300
Entry Wire Line
	12750 2300 12850 2400
Entry Wire Line
	12750 2400 12850 2500
Entry Wire Line
	11100 1500 11000 1600
Entry Wire Line
	11100 1600 11000 1700
Wire Wire Line
	11100 1700 11400 1700
Entry Wire Line
	11100 1700 11000 1800
Entry Wire Line
	11100 1800 11000 1900
Entry Wire Line
	11100 1900 11000 2000
Entry Wire Line
	11100 2000 11000 2100
Entry Wire Line
	11100 2200 11000 2300
$Comp
L custom_library:HV5812 D4
U 1 1 5E0D2C2D
P 11900 1950
F 0 "D4" H 11550 2800 50  0000 C CNN
F 1 "HV5812" H 11650 1100 50  0000 C CNN
F 2 "Package_SO:SOIC-28W_7.5x17.9mm_P1.27mm" H 11900 2800 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20005629A.pdf" H 11900 2800 50  0001 C CNN
	1    11900 1950
	1    0    0    -1  
$EndComp
Entry Wire Line
	13900 1150 13800 1250
Entry Wire Line
	13900 1250 13800 1350
Entry Wire Line
	13900 1350 13800 1450
Entry Wire Line
	13900 1450 13800 1550
Entry Wire Line
	13900 1550 13800 1650
Entry Wire Line
	13900 1650 13800 1750
Entry Wire Line
	13900 1750 13800 1850
Entry Wire Line
	13900 1850 13800 1950
Entry Wire Line
	13900 1950 13800 2050
Entry Wire Line
	13900 2050 13800 2150
Wire Wire Line
	13900 1150 14150 1150
Wire Wire Line
	14150 1250 13900 1250
Wire Wire Line
	13900 1350 14150 1350
Wire Wire Line
	14150 1450 13900 1450
Wire Wire Line
	13900 1550 14150 1550
Wire Wire Line
	14150 1650 13900 1650
Wire Wire Line
	13900 1750 14150 1750
Wire Wire Line
	14150 1850 13900 1850
Wire Wire Line
	13900 1950 14150 1950
Wire Wire Line
	14150 2050 13900 2050
Entry Wire Line
	13900 2650 13800 2750
Entry Wire Line
	13900 2750 13800 2850
Entry Wire Line
	13900 2850 13800 2950
Entry Wire Line
	13900 2950 13800 3050
Entry Wire Line
	13900 3050 13800 3150
Entry Wire Line
	13900 3150 13800 3250
Entry Wire Line
	13900 3250 13800 3350
Entry Wire Line
	13900 3350 13800 3450
Entry Wire Line
	13900 3450 13800 3550
Entry Wire Line
	13900 3550 13800 3650
Wire Wire Line
	14150 2650 13900 2650
Wire Wire Line
	13900 2750 14150 2750
Wire Wire Line
	14150 2850 13900 2850
Wire Wire Line
	13900 2950 14150 2950
Wire Wire Line
	14150 3050 13900 3050
Wire Wire Line
	13900 3150 14150 3150
Wire Wire Line
	14150 3250 13900 3250
Wire Wire Line
	13900 3350 14150 3350
Wire Wire Line
	14150 3450 13900 3450
Wire Wire Line
	13900 3550 14150 3550
Text Label 13950 1150 0    50   ~ 0
1-0
Text Label 13950 1250 0    50   ~ 0
1-9
Text Label 13950 1350 0    50   ~ 0
1-8
Text Label 13950 1450 0    50   ~ 0
1-7
Text Label 13950 1550 0    50   ~ 0
1-6
Text Label 13950 1650 0    50   ~ 0
1-5
Text Label 13950 1750 0    50   ~ 0
1-4
Text Label 13950 1850 0    50   ~ 0
1-3
Text Label 13950 1950 0    50   ~ 0
1-2
Text Label 13950 2050 0    50   ~ 0
1-1
Text Label 13950 2650 0    50   ~ 0
2-0
Text Label 13950 2750 0    50   ~ 0
2-9
Text Label 13950 2850 0    50   ~ 0
2-8
Text Label 13950 2950 0    50   ~ 0
2-7
Text Label 13950 3050 0    50   ~ 0
2-6
Text Label 13950 3150 0    50   ~ 0
2-5
Text Label 13950 3250 0    50   ~ 0
2-4
Text Label 13950 3350 0    50   ~ 0
2-3
Text Label 13950 3450 0    50   ~ 0
2-2
Text Label 13950 3550 0    50   ~ 0
2-1
$Comp
L custom_library:IN-12B LL3
U 1 1 5E145DF2
P 14350 4600
F 0 "LL3" H 14375 5065 50  0000 C CNN
F 1 "IN-12B" H 14375 4974 50  0000 C CNN
F 2 "clock:PL31" H 14350 4950 50  0001 C CNN
F 3 "https://istok2.com/data/1719/" H 14350 4950 50  0001 C CNN
	1    14350 4600
	1    0    0    -1  
$EndComp
$Comp
L custom_library:IN-12B LL4
U 1 1 5E145DF8
P 14350 6100
F 0 "LL4" H 14375 6565 50  0000 C CNN
F 1 "IN-12B" H 14375 6474 50  0000 C CNN
F 2 "clock:PL31" H 14350 6450 50  0001 C CNN
F 3 "https://istok2.com/data/1719/" H 14350 6450 50  0001 C CNN
	1    14350 6100
	1    0    0    -1  
$EndComp
Text Label 11150 5050 0    50   ~ 0
3-0
Wire Wire Line
	12750 4750 12500 4750
Wire Wire Line
	12750 4850 12500 4850
Wire Wire Line
	12750 4950 12500 4950
Wire Wire Line
	12750 5050 12500 5050
Wire Wire Line
	12750 5150 12500 5150
Wire Wire Line
	12750 5250 12500 5250
Wire Wire Line
	12750 5350 12500 5350
Wire Wire Line
	12750 5450 12500 5450
Wire Wire Line
	12750 5550 12500 5550
Wire Wire Line
	12750 5650 12500 5650
Wire Wire Line
	11400 4750 11100 4750
Wire Wire Line
	11400 4850 11100 4850
Wire Wire Line
	11400 5050 11100 5050
Wire Wire Line
	11100 5150 11400 5150
Wire Wire Line
	11400 5250 11100 5250
Wire Wire Line
	11100 5350 11400 5350
Wire Wire Line
	11400 5450 11100 5450
Wire Wire Line
	11100 5550 11400 5550
Wire Wire Line
	11400 5650 11100 5650
Entry Wire Line
	12750 4750 12850 4850
Entry Wire Line
	12750 4850 12850 4950
Entry Wire Line
	12750 4950 12850 5050
Entry Wire Line
	12750 5050 12850 5150
Entry Wire Line
	12750 5150 12850 5250
Entry Wire Line
	12750 5250 12850 5350
Entry Wire Line
	12750 5350 12850 5450
Entry Wire Line
	12750 5450 12850 5550
Entry Wire Line
	12750 5550 12850 5650
Entry Wire Line
	12750 5650 12850 5750
Entry Wire Line
	11100 4750 11000 4850
Entry Wire Line
	11100 4850 11000 4950
Wire Wire Line
	11100 4950 11400 4950
Entry Wire Line
	11100 4950 11000 5050
Entry Wire Line
	11100 5050 11000 5150
Entry Wire Line
	11100 5150 11000 5250
Entry Wire Line
	11100 5250 11000 5350
Entry Wire Line
	11100 5350 11000 5450
Entry Wire Line
	11100 5450 11000 5550
Entry Wire Line
	11100 5550 11000 5650
Entry Wire Line
	11100 5650 11000 5750
Entry Wire Line
	13900 4400 13800 4500
Entry Wire Line
	13900 4500 13800 4600
Entry Wire Line
	13900 4600 13800 4700
Entry Wire Line
	13900 4700 13800 4800
Entry Wire Line
	13900 4800 13800 4900
Entry Wire Line
	13900 4900 13800 5000
Entry Wire Line
	13900 5000 13800 5100
Entry Wire Line
	13900 5100 13800 5200
Entry Wire Line
	13900 5200 13800 5300
Entry Wire Line
	13900 5300 13800 5400
Wire Wire Line
	13900 4400 14150 4400
Wire Wire Line
	14150 4500 13900 4500
Wire Wire Line
	13900 4600 14150 4600
Wire Wire Line
	14150 4700 13900 4700
Wire Wire Line
	13900 4800 14150 4800
Wire Wire Line
	14150 4900 13900 4900
Wire Wire Line
	13900 5000 14150 5000
Wire Wire Line
	14150 5100 13900 5100
Wire Wire Line
	13900 5200 14150 5200
Wire Wire Line
	14150 5300 13900 5300
Entry Wire Line
	13900 5900 13800 6000
Entry Wire Line
	13900 6000 13800 6100
Entry Wire Line
	13900 6100 13800 6200
Entry Wire Line
	13900 6200 13800 6300
Entry Wire Line
	13900 6300 13800 6400
Entry Wire Line
	13900 6400 13800 6500
Entry Wire Line
	13900 6500 13800 6600
Entry Wire Line
	13900 6600 13800 6700
Entry Wire Line
	13900 6700 13800 6800
Entry Wire Line
	13900 6800 13800 6900
Wire Wire Line
	14150 5900 13900 5900
Wire Wire Line
	13900 6000 14150 6000
Wire Wire Line
	14150 6100 13900 6100
Wire Wire Line
	13900 6200 14150 6200
Wire Wire Line
	14150 6300 13900 6300
Wire Wire Line
	13900 6400 14150 6400
Wire Wire Line
	14150 6500 13900 6500
Wire Wire Line
	13900 6600 14150 6600
Wire Wire Line
	14150 6700 13900 6700
Wire Wire Line
	13900 6800 14150 6800
Text Label 13950 4400 0    50   ~ 0
3-0
Text Label 13950 4500 0    50   ~ 0
3-9
Text Label 13950 4600 0    50   ~ 0
3-8
Text Label 13950 4700 0    50   ~ 0
3-7
Text Label 13950 4800 0    50   ~ 0
3-6
Text Label 13950 4900 0    50   ~ 0
3-5
Text Label 13950 5000 0    50   ~ 0
3-4
Text Label 13950 5100 0    50   ~ 0
3-3
Text Label 13950 5200 0    50   ~ 0
3-2
Text Label 13950 5300 0    50   ~ 0
3-1
Text Label 13950 5900 0    50   ~ 0
4-0
Text Label 13950 6000 0    50   ~ 0
4-9
Text Label 13950 6100 0    50   ~ 0
4-8
Text Label 13950 6200 0    50   ~ 0
4-7
Text Label 13950 6300 0    50   ~ 0
4-6
Text Label 13950 6400 0    50   ~ 0
4-5
Text Label 13950 6500 0    50   ~ 0
4-4
Text Label 13950 6600 0    50   ~ 0
4-3
Text Label 13950 6700 0    50   ~ 0
4-2
Text Label 13950 6800 0    50   ~ 0
4-1
Text Label 11150 1700 0    50   ~ 0
1-9
Text Label 11150 1600 0    50   ~ 0
1-8
Text Label 11150 1500 0    50   ~ 0
1-7
Text Label 12550 2000 0    50   ~ 0
1-6
Text Label 12550 1900 0    50   ~ 0
1-5
Text Label 12550 1800 0    50   ~ 0
1-4
Text Label 12550 1700 0    50   ~ 0
1-3
Text Label 12550 1600 0    50   ~ 0
1-2
Text Label 12550 1500 0    50   ~ 0
1-1
Text Label 12550 2400 0    50   ~ 0
2-0
Text Label 12550 2300 0    50   ~ 0
2-9
Text Label 12550 2200 0    50   ~ 0
2-8
Text Label 12550 2100 0    50   ~ 0
2-7
Text Label 11150 2400 0    50   ~ 0
2-6
Text Label 11150 2300 0    50   ~ 0
2-5
Text Label 11150 2200 0    50   ~ 0
2-4
Text Label 11150 2100 0    50   ~ 0
2-3
Text Label 11150 2000 0    50   ~ 0
2-2
Text Label 11150 1900 0    50   ~ 0
2-1
Wire Wire Line
	12500 1400 13200 1400
$Comp
L custom_library:HV5812 D5
U 1 1 5E145E27
P 11900 5200
F 0 "D5" H 11550 6050 50  0000 C CNN
F 1 "HV5812" H 11650 4350 50  0000 C CNN
F 2 "Package_SO:SOIC-28W_7.5x17.9mm_P1.27mm" H 11900 6050 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20005629A.pdf" H 11900 6050 50  0001 C CNN
	1    11900 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	12500 2500 12650 2500
Wire Wire Line
	12650 2500 12650 2600
Wire Wire Line
	12500 2600 12650 2600
Connection ~ 12650 2600
Wire Wire Line
	12650 2600 12650 2800
$Comp
L power:GND #PWR0102
U 1 1 5E11A0F6
P 12650 2800
F 0 "#PWR0102" H 12650 2550 50  0001 C CNN
F 1 "GND" H 12655 2627 50  0000 C CNN
F 2 "" H 12650 2800 50  0001 C CNN
F 3 "" H 12650 2800 50  0001 C CNN
	1    12650 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	12500 5750 12650 5750
Wire Wire Line
	12650 5750 12650 5850
Wire Wire Line
	12500 5850 12650 5850
Connection ~ 12650 5850
Wire Wire Line
	12650 5850 12650 6150
$Comp
L power:GND #PWR0103
U 1 1 5E126BC2
P 12650 6150
F 0 "#PWR0103" H 12650 5900 50  0001 C CNN
F 1 "GND" H 12655 5977 50  0000 C CNN
F 2 "" H 12650 6150 50  0001 C CNN
F 3 "" H 12650 6150 50  0001 C CNN
	1    12650 6150
	1    0    0    -1  
$EndComp
Text Label 11150 4950 0    50   ~ 0
3-9
Text Label 11150 4850 0    50   ~ 0
3-8
Text Label 11150 4750 0    50   ~ 0
3-7
Text Label 12550 5250 0    50   ~ 0
3-6
Text Label 12550 5150 0    50   ~ 0
3-5
Text Label 12550 5050 0    50   ~ 0
3-4
Text Label 12550 4950 0    50   ~ 0
3-3
Text Label 12550 4850 0    50   ~ 0
3-2
Text Label 12550 4750 0    50   ~ 0
3-1
Text Label 12550 5550 0    50   ~ 0
4-9
Text Label 12550 5450 0    50   ~ 0
4-8
Text Label 12550 5350 0    50   ~ 0
4-7
Text Label 11150 5650 0    50   ~ 0
4-6
Text Label 11150 5550 0    50   ~ 0
4-5
Text Label 11150 5450 0    50   ~ 0
4-4
Text Label 11150 5350 0    50   ~ 0
4-3
Text Label 11150 5250 0    50   ~ 0
4-2
Text Label 11150 5150 0    50   ~ 0
4-1
Wire Wire Line
	11400 2600 10550 2600
Wire Wire Line
	10550 5850 11400 5850
$Comp
L Device:R R10
U 1 1 5E1F2E8D
P 14850 1650
F 0 "R10" V 15050 1700 50  0000 L CNN
F 1 "22K" V 14950 1650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 14780 1650 50  0001 C CNN
F 3 "~" H 14850 1650 50  0001 C CNN
	1    14850 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	15200 1450 15200 1650
Wire Wire Line
	15200 1650 15000 1650
Wire Wire Line
	14700 1650 14600 1650
$Comp
L Device:R R11
U 1 1 5E22872D
P 14850 3150
F 0 "R11" V 15050 3200 50  0000 L CNN
F 1 "22K" V 14950 3150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 14780 3150 50  0001 C CNN
F 3 "~" H 14850 3150 50  0001 C CNN
	1    14850 3150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R12
U 1 1 5E2299F6
P 14850 4900
F 0 "R12" V 15050 4950 50  0000 L CNN
F 1 "22K" V 14950 4900 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 14780 4900 50  0001 C CNN
F 3 "~" H 14850 4900 50  0001 C CNN
	1    14850 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R13
U 1 1 5E229E0F
P 14850 6400
F 0 "R13" V 15050 6450 50  0000 L CNN
F 1 "22K" V 14950 6400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 14780 6400 50  0001 C CNN
F 3 "~" H 14850 6400 50  0001 C CNN
	1    14850 6400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	15200 1650 15200 3150
Wire Wire Line
	15200 3150 15000 3150
Connection ~ 15200 1650
Wire Wire Line
	14700 3150 14600 3150
Wire Wire Line
	15200 3150 15200 4900
Wire Wire Line
	15200 4900 15000 4900
Connection ~ 15200 3150
Wire Wire Line
	14700 4900 14600 4900
Wire Wire Line
	14600 6400 14700 6400
Wire Wire Line
	15200 4900 15200 6400
Wire Wire Line
	15200 6400 15000 6400
Connection ~ 15200 4900
$Comp
L custom_library:HV #PWR0104
U 1 1 5E27A3B6
P 15200 1450
F 0 "#PWR0104" H 15200 1300 50  0001 C CNN
F 1 "HV" H 15200 1623 50  0000 C CNN
F 2 "" H 15200 1450 50  0001 C CNN
F 3 "" H 15200 1450 50  0001 C CNN
	1    15200 1450
	1    0    0    -1  
$EndComp
$Comp
L custom_library:HV #PWR0105
U 1 1 5E27AC11
P 7400 7600
F 0 "#PWR0105" H 7400 7450 50  0001 C CNN
F 1 "HV" H 7400 7750 50  0000 C CNN
F 2 "" H 7400 7600 50  0001 C CNN
F 3 "" H 7400 7600 50  0001 C CNN
	1    7400 7600
	1    0    0    -1  
$EndComp
Connection ~ 7400 7700
Wire Wire Line
	7400 7700 7550 7700
$Comp
L Diode:1N47xxA D3
U 1 1 5E28F1CC
P 9000 8550
F 0 "D3" V 8954 8629 50  0000 L CNN
F 1 "1N4764A" V 9045 8629 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 9000 8375 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85816/1n4728a.pdf" H 9000 8550 50  0001 C CNN
	1    9000 8550
	0    1    1    0   
$EndComp
Wire Wire Line
	7400 8500 7400 8950
$Comp
L Device:R R7
U 1 1 5E0B7AE7
P 7550 8850
F 0 "R7" H 7620 8896 50  0000 L CNN
F 1 "10K" H 7620 8805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7480 8850 50  0001 C CNN
F 3 "~" H 7550 8850 50  0001 C CNN
	1    7550 8850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5E29AAB6
P 8650 7700
F 0 "R9" V 8550 7650 50  0000 L CNN
F 1 "150K" V 8750 7600 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8580 7700 50  0001 C CNN
F 3 "~" H 8650 7700 50  0001 C CNN
	1    8650 7700
	0    1    1    0   
$EndComp
$Comp
L Diode:1.5KExxCA D2
U 1 1 5E29C12F
P 8150 8600
F 0 "D2" V 8104 8679 50  0000 L CNN
F 1 "1.5KE220CA" V 8195 8679 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AE_P15.24mm_Horizontal" H 8150 8400 50  0001 C CNN
F 3 "https://www.vishay.com/docs/88301/15ke.pdf" H 8150 8600 50  0001 C CNN
	1    8150 8600
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 5E29C85D
P 8150 8150
F 0 "R8" H 8220 8196 50  0000 L CNN
F 1 "1" H 8220 8105 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 8080 8150 50  0001 C CNN
F 3 "~" H 8150 8150 50  0001 C CNN
	1    8150 8150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 7700 8150 7700
Wire Wire Line
	8150 7700 8150 8000
Connection ~ 7550 7700
Wire Wire Line
	8150 8300 8150 8450
Wire Wire Line
	7700 9300 8150 9300
Wire Wire Line
	8150 9300 8150 8750
Connection ~ 7700 9300
Wire Wire Line
	8500 7700 8150 7700
Connection ~ 8150 7700
Wire Wire Line
	8800 7700 9000 7700
Wire Wire Line
	9000 7700 9000 8400
Wire Wire Line
	9000 8700 9000 9300
Wire Wire Line
	9000 9300 8150 9300
Connection ~ 8150 9300
$Comp
L custom_library:HV_C #PWR0106
U 1 1 5E2DBBA1
P 9000 7600
F 0 "#PWR0106" H 9000 7450 50  0001 C CNN
F 1 "HV_C" H 9000 7773 50  0000 C CNN
F 2 "" H 9000 7600 50  0001 C CNN
F 3 "" H 9000 7600 50  0001 C CNN
	1    9000 7600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 7600 9000 7700
Connection ~ 9000 7700
Wire Wire Line
	7400 7600 7400 7700
Text Label 4700 5050 0    50   ~ 0
STROBE
Text Label 4700 5150 0    50   ~ 0
CLOCK
Text Label 4700 4950 0    50   ~ 0
DATA
$Comp
L Device:CP C1
U 1 1 5E121FA8
P 3550 8350
F 0 "C1" H 3650 8450 50  0000 R CNN
F 1 "220uF, 16V" V 3700 8900 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 3588 8200 50  0001 C CNN
F 3 "~" H 3550 8350 50  0001 C CNN
	1    3550 8350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E122EB0
P 3900 8350
F 0 "C2" H 3950 8450 50  0000 L CNN
F 1 "10uF, 10V" V 4100 8400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1210_3225Metric_Pad1.42x2.65mm_HandSolder" H 3938 8200 50  0001 C CNN
F 3 "~" H 3900 8350 50  0001 C CNN
	1    3900 8350
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder_Switch SW1
U 1 1 5E15B558
P 8400 4250
F 0 "SW1" H 8400 4617 50  0000 C CNN
F 1 "PEC16" H 8400 4526 50  0000 C CNN
F 2 "clock:RotaryEncoder_Bouruns_PEC16" H 8250 4410 50  0001 C CNN
F 3 "~" H 8400 4510 50  0001 C CNN
	1    8400 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E1697E9
P 4650 8800
F 0 "R1" H 4720 8846 50  0000 L CNN
F 1 "10K" H 4720 8755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4580 8800 50  0001 C CNN
F 3 "~" H 4650 8800 50  0001 C CNN
	1    4650 8800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 8450 4650 8650
Wire Wire Line
	4650 8450 5000 8450
Wire Wire Line
	4650 8950 4650 9300
Wire Wire Line
	4650 9300 5250 9300
Text Label 4700 8450 0    50   ~ 0
SHUT
$Comp
L power:+5V #PWR0107
U 1 1 5E183B75
P 3150 3150
F 0 "#PWR0107" H 3150 3000 50  0001 C CNN
F 1 "+5V" V 3165 3278 50  0000 L CNN
F 2 "" H 3150 3150 50  0001 C CNN
F 3 "" H 3150 3150 50  0001 C CNN
	1    3150 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5E184A1C
P 3450 5850
F 0 "#PWR0108" H 3450 5600 50  0001 C CNN
F 1 "GND" V 3550 5800 50  0000 C CNN
F 2 "" H 3450 5850 50  0001 C CNN
F 3 "" H 3450 5850 50  0001 C CNN
	1    3450 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5E19F6DD
P 7850 3800
F 0 "R3" H 7920 3846 50  0000 L CNN
F 1 "10K" H 7920 3755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7780 3800 50  0001 C CNN
F 3 "~" H 7850 3800 50  0001 C CNN
	1    7850 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5E19FE45
P 7500 3800
F 0 "R2" H 7570 3846 50  0000 L CNN
F 1 "10K" H 7570 3755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7430 3800 50  0001 C CNN
F 3 "~" H 7500 3800 50  0001 C CNN
	1    7500 3800
	1    0    0    -1  
$EndComp
Connection ~ 5350 7700
Wire Wire Line
	4650 9300 3900 9300
Connection ~ 4650 9300
Wire Wire Line
	3550 8200 3550 7700
Wire Wire Line
	3550 7700 3900 7700
Wire Wire Line
	3900 8200 3900 7700
Connection ~ 3900 7700
Wire Wire Line
	3900 7700 5350 7700
Wire Wire Line
	3550 8500 3550 9300
Wire Wire Line
	3900 8500 3900 9300
Connection ~ 3900 9300
Wire Wire Line
	3900 9300 3550 9300
$Comp
L power:GND #PWR0110
U 1 1 5E230FCE
P 6400 5050
F 0 "#PWR0110" H 6400 4800 50  0001 C CNN
F 1 "GND" V 6405 4877 50  0000 C CNN
F 2 "" H 6400 5050 50  0001 C CNN
F 3 "" H 6400 5050 50  0001 C CNN
	1    6400 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 4250 8000 4250
Wire Wire Line
	7850 3950 7850 4150
Wire Wire Line
	7850 4150 8100 4150
Wire Wire Line
	7850 3650 7850 3550
Wire Wire Line
	7850 3550 7500 3550
Wire Wire Line
	7500 3550 7500 3650
$Comp
L power:+5V #PWR0111
U 1 1 5E282131
P 8850 3450
F 0 "#PWR0111" H 8850 3300 50  0001 C CNN
F 1 "+5V" H 8865 3623 50  0000 C CNN
F 2 "" H 8850 3450 50  0001 C CNN
F 3 "" H 8850 3450 50  0001 C CNN
	1    8850 3450
	1    0    0    -1  
$EndComp
Connection ~ 7850 3550
$Comp
L Device:R R5
U 1 1 5E282CDF
P 8850 3800
F 0 "R5" H 8920 3846 50  0000 L CNN
F 1 "10K" H 8920 3755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8780 3800 50  0001 C CNN
F 3 "~" H 8850 3800 50  0001 C CNN
	1    8850 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 4150 8850 4150
Wire Wire Line
	8850 4150 8850 3950
Wire Wire Line
	8700 4350 8950 4350
Wire Wire Line
	8850 4150 8850 4550
Connection ~ 8850 4150
Wire Wire Line
	8850 3650 8850 3550
Wire Wire Line
	8850 3550 7850 3550
Wire Wire Line
	8850 3450 8850 3550
Connection ~ 8850 3550
Text Label 4650 4150 0    50   ~ 0
A
Text Label 4650 4250 0    50   ~ 0
B
Text Label 4700 5250 0    50   ~ 0
SW
$Comp
L power:GND #PWR0114
U 1 1 5E4164D4
P 12600 9600
F 0 "#PWR0114" H 12600 9350 50  0001 C CNN
F 1 "GND" H 12605 9427 50  0000 C CNN
F 2 "" H 12600 9600 50  0001 C CNN
F 3 "" H 12600 9600 50  0001 C CNN
	1    12600 9600
	1    0    0    -1  
$EndComp
$Comp
L custom_library:HV_C #PWR0116
U 1 1 5E47AE2C
P 12700 4050
F 0 "#PWR0116" H 12700 3900 50  0001 C CNN
F 1 "HV_C" H 12850 4100 50  0000 C CNN
F 2 "" H 12700 4050 50  0001 C CNN
F 3 "" H 12700 4050 50  0001 C CNN
	1    12700 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5E47AE32
P 12250 4050
F 0 "C10" V 12150 3900 50  0000 L CNN
F 1 "100nF, 250V" V 12400 3850 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 12288 3900 50  0001 C CNN
F 3 "~" H 12250 4050 50  0001 C CNN
	1    12250 4050
	0    1    1    0   
$EndComp
$Comp
L Device:C C7
U 1 1 5E47AE38
P 11650 4050
F 0 "C7" V 11550 3900 50  0000 L CNN
F 1 "100nF, 50V" V 11800 3850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 11688 3900 50  0001 C CNN
F 3 "~" H 11650 4050 50  0001 C CNN
	1    11650 4050
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0117
U 1 1 5E47AE3E
P 11200 4050
F 0 "#PWR0117" H 11200 3900 50  0001 C CNN
F 1 "+5V" H 11300 4150 50  0000 C CNN
F 2 "" H 11200 4050 50  0001 C CNN
F 3 "" H 11200 4050 50  0001 C CNN
	1    11200 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	12400 4050 12700 4050
Wire Wire Line
	12700 4050 12700 4550
Connection ~ 12700 4050
Wire Wire Line
	12100 4050 11950 4050
Wire Wire Line
	11200 4550 11200 4050
Wire Wire Line
	11200 4050 11500 4050
Connection ~ 11200 4050
$Comp
L power:GND #PWR0118
U 1 1 5E47AE4B
P 11950 4150
F 0 "#PWR0118" H 11950 3900 50  0001 C CNN
F 1 "GND" H 11955 3977 50  0000 C CNN
F 2 "" H 11950 4150 50  0001 C CNN
F 3 "" H 11950 4150 50  0001 C CNN
	1    11950 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	11950 4150 11950 4050
Connection ~ 11950 4050
Wire Wire Line
	11950 4050 11800 4050
Wire Wire Line
	11400 4550 11200 4550
Wire Wire Line
	12500 4550 12700 4550
$Comp
L custom_library:HV_C #PWR0119
U 1 1 5E590B03
P 12700 800
F 0 "#PWR0119" H 12700 650 50  0001 C CNN
F 1 "HV_C" H 12700 973 50  0000 C CNN
F 2 "" H 12700 800 50  0001 C CNN
F 3 "" H 12700 800 50  0001 C CNN
	1    12700 800 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 5E590B09
P 12250 800
F 0 "C9" V 12150 650 50  0000 L CNN
F 1 "100nF, 250V" V 12400 600 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 12288 650 50  0001 C CNN
F 3 "~" H 12250 800 50  0001 C CNN
	1    12250 800 
	0    1    1    0   
$EndComp
$Comp
L Device:C C6
U 1 1 5E590B0F
P 11650 800
F 0 "C6" V 11550 650 50  0000 L CNN
F 1 "100nF, 50V" V 11800 600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 11688 650 50  0001 C CNN
F 3 "~" H 11650 800 50  0001 C CNN
	1    11650 800 
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0120
U 1 1 5E590B15
P 11200 800
F 0 "#PWR0120" H 11200 650 50  0001 C CNN
F 1 "+5V" H 11215 973 50  0000 C CNN
F 2 "" H 11200 800 50  0001 C CNN
F 3 "" H 11200 800 50  0001 C CNN
	1    11200 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	12400 800  12700 800 
Wire Wire Line
	12700 800  12700 1300
Connection ~ 12700 800 
Wire Wire Line
	12100 800  11950 800 
Wire Wire Line
	11200 1300 11200 800 
Wire Wire Line
	11200 800  11500 800 
Connection ~ 11200 800 
$Comp
L power:GND #PWR0121
U 1 1 5E590B22
P 11950 900
F 0 "#PWR0121" H 11950 650 50  0001 C CNN
F 1 "GND" H 11955 727 50  0000 C CNN
F 2 "" H 11950 900 50  0001 C CNN
F 3 "" H 11950 900 50  0001 C CNN
	1    11950 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	11950 900  11950 800 
Connection ~ 11950 800 
Wire Wire Line
	11950 800  11800 800 
Wire Wire Line
	12700 1300 12500 1300
Wire Wire Line
	11400 1300 11200 1300
Text Label 12550 5650 0    50   ~ 0
4-0
Text Label 13950 2150 0    50   ~ 0
1-.
Text Label 13950 3650 0    50   ~ 0
2-.
Text Label 13950 5400 0    50   ~ 0
3-.
Text Label 12900 9250 0    50   ~ 0
4-.
$Comp
L custom_library:IN-12B LL1
U 1 1 5E0CFD11
P 14350 1350
F 0 "LL1" H 14375 1815 50  0000 C CNN
F 1 "IN-12B" H 14375 1724 50  0000 C CNN
F 2 "clock:PL31" H 14350 1700 50  0001 C CNN
F 3 "https://istok2.com/data/1719/" H 14350 1700 50  0001 C CNN
	1    14350 1350
	1    0    0    -1  
$EndComp
Entry Wire Line
	13800 2250 13900 2150
Wire Wire Line
	14150 2150 13900 2150
Entry Wire Line
	13800 3750 13900 3650
Wire Wire Line
	14150 3650 13900 3650
Connection ~ 11000 3750
Wire Bus Line
	13800 7150 12850 7150
Wire Bus Line
	12850 7150 11000 7150
Connection ~ 12850 7150
Wire Wire Line
	14150 5400 13900 5400
Wire Wire Line
	14150 6900 13900 6900
Text Label 13950 6900 0    50   ~ 0
4-.
Text Label 12900 8700 0    50   ~ 0
3-.
Text Label 12900 8150 0    50   ~ 0
2-.
Text Label 12900 7600 0    50   ~ 0
1-.
Wire Wire Line
	10350 5300 10350 4650
Wire Wire Line
	10350 4650 11400 4650
Wire Wire Line
	13100 4650 13100 3900
Wire Wire Line
	13100 3900 10800 3900
Wire Wire Line
	10800 3900 10800 1400
Wire Wire Line
	10800 1400 11400 1400
Wire Wire Line
	12500 4650 13100 4650
$Comp
L Device:R R14
U 1 1 5E20239B
P 5550 4150
F 0 "R14" V 5350 4100 50  0000 L CNN
F 1 "1K" V 5450 4100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5480 4150 50  0001 C CNN
F 3 "~" H 5550 4150 50  0001 C CNN
	1    5550 4150
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 5E21BF0A
P 5850 4250
F 0 "R15" V 5650 4200 50  0000 L CNN
F 1 "1K" V 5750 4200 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5780 4250 50  0001 C CNN
F 3 "~" H 5850 4250 50  0001 C CNN
	1    5850 4250
	0    1    1    0   
$EndComp
$Comp
L Device:R R16
U 1 1 5E21C592
P 6150 4350
F 0 "R16" V 5950 4300 50  0000 L CNN
F 1 "1K" V 6050 4300 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6080 4350 50  0001 C CNN
F 3 "~" H 6150 4350 50  0001 C CNN
	1    6150 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 4900 6400 5050
Wire Wire Line
	6400 5050 6750 5050
Wire Wire Line
	8950 4350 8950 5050
Connection ~ 6400 5050
Wire Wire Line
	6750 4900 6750 5050
Connection ~ 6750 5050
Wire Wire Line
	6750 5050 7100 5050
Wire Wire Line
	7100 4900 7100 5050
Connection ~ 7100 5050
Wire Wire Line
	7100 5050 8000 5050
Wire Wire Line
	6400 4600 6400 4350
Wire Wire Line
	6400 4350 6300 4350
Wire Wire Line
	6750 4600 6750 4250
Wire Wire Line
	6750 4250 6000 4250
Wire Wire Line
	7100 4600 7100 4150
Wire Wire Line
	7100 4150 5700 4150
Text Label 6500 4150 0    50   ~ 0
_A
Text Label 6500 4250 0    50   ~ 0
_B
Text Label 6350 4350 0    50   ~ 0
_SW
Wire Wire Line
	7100 4150 7850 4150
Connection ~ 7100 4150
Connection ~ 7850 4150
Wire Wire Line
	6750 4250 7350 4250
Wire Wire Line
	7350 4250 7350 4350
Wire Wire Line
	7350 4350 7500 4350
Connection ~ 6750 4250
Wire Wire Line
	7500 3950 7500 4350
Connection ~ 7500 4350
Wire Wire Line
	7500 4350 8100 4350
Wire Wire Line
	8000 4250 8000 5050
Connection ~ 8000 5050
Wire Wire Line
	8000 5050 8950 5050
Wire Wire Line
	6400 4350 7250 4350
Wire Wire Line
	7250 4350 7250 4550
Wire Wire Line
	7250 4550 8850 4550
Connection ~ 6400 4350
$Comp
L Device:C C12
U 1 1 5E49F6EA
P 6400 4750
F 0 "C12" V 6300 4600 50  0000 L CNN
F 1 "100nF, 50V" V 6550 4550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6438 4600 50  0001 C CNN
F 3 "~" H 6400 4750 50  0001 C CNN
	1    6400 4750
	-1   0    0    1   
$EndComp
$Comp
L Device:C C13
U 1 1 5E4A1492
P 6750 4750
F 0 "C13" V 6650 4600 50  0000 L CNN
F 1 "100nF, 50V" V 6900 4550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6788 4600 50  0001 C CNN
F 3 "~" H 6750 4750 50  0001 C CNN
	1    6750 4750
	-1   0    0    1   
$EndComp
$Comp
L Device:C C14
U 1 1 5E4A17BF
P 7100 4750
F 0 "C14" V 7000 4600 50  0000 L CNN
F 1 "100nF, 50V" V 7250 4550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7138 4600 50  0001 C CNN
F 3 "~" H 7100 4750 50  0001 C CNN
	1    7100 4750
	-1   0    0    1   
$EndComp
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 5E28A675
P 3350 4550
F 0 "A1" H 3100 5600 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 2850 5500 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 3350 4550 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 3350 4550 50  0001 C CNN
	1    3350 4550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10550 5500 10550 5850
Wire Wire Line
	10550 2600 10550 5500
Connection ~ 10550 5500
Wire Wire Line
	5400 4150 3850 4150
Wire Wire Line
	3850 4250 5700 4250
Wire Wire Line
	3250 5650 3350 5650
Connection ~ 3350 5650
Wire Wire Line
	3350 5650 3450 5650
Wire Wire Line
	3450 5650 3450 5850
Connection ~ 3450 5650
Wire Wire Line
	10450 5400 10450 5750
Wire Wire Line
	3450 3150 3450 3550
$Comp
L custom_library:ZS-042 U1
U 1 1 5E5AFEC8
P 1700 2850
F 0 "U1" H 2100 3115 50  0000 C CNN
F 1 "ZS-042" H 2100 3024 50  0000 C CNN
F 2 "clock:zs-042" H 1700 2850 50  0001 C CNN
F 3 "" H 1700 2850 50  0001 C CNN
	1    1700 2850
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0109
U 1 1 5E5CF941
P 3250 3150
F 0 "#PWR0109" H 3250 3000 50  0001 C CNN
F 1 "+3.3V" V 3265 3323 50  0000 C CNN
F 2 "" H 3250 3150 50  0001 C CNN
F 3 "" H 3250 3150 50  0001 C CNN
	1    3250 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3150 3150 3550
Wire Wire Line
	3250 3150 3250 3250
$Comp
L power:+VDC #PWR0122
U 1 1 5E60A8F7
P 3450 3150
F 0 "#PWR0122" H 3450 3050 50  0001 C CNN
F 1 "+VDC" H 3450 3425 50  0000 C CNN
F 2 "" H 3450 3150 50  0001 C CNN
F 3 "" H 3450 3150 50  0001 C CNN
	1    3450 3150
	1    0    0    -1  
$EndComp
$Comp
L power:+VDC #PWR0123
U 1 1 5E60BD5A
P 3550 7450
F 0 "#PWR0123" H 3550 7350 50  0001 C CNN
F 1 "+VDC" H 3550 7725 50  0000 C CNN
F 2 "" H 3550 7450 50  0001 C CNN
F 3 "" H 3550 7450 50  0001 C CNN
	1    3550 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 7450 3550 7700
Connection ~ 3550 7700
Wire Wire Line
	1700 3150 2150 3150
Wire Wire Line
	2150 3150 2150 4950
Wire Wire Line
	2150 4950 2850 4950
Wire Wire Line
	2850 5050 2250 5050
Wire Wire Line
	2250 5050 2250 3050
Wire Wire Line
	2250 3050 1700 3050
Text Label 2400 4950 0    50   ~ 0
SDA
Text Label 2400 5050 0    50   ~ 0
SCL
Wire Wire Line
	1700 3250 3250 3250
Connection ~ 3250 3250
Wire Wire Line
	3250 3250 3250 3550
$Comp
L power:GND #PWR0124
U 1 1 5E6A3837
P 1800 3450
F 0 "#PWR0124" H 1800 3200 50  0001 C CNN
F 1 "GND" V 1900 3400 50  0000 C CNN
F 2 "" H 1800 3450 50  0001 C CNN
F 3 "" H 1800 3450 50  0001 C CNN
	1    1800 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 3350 1800 3350
Wire Wire Line
	1800 3350 1800 3450
Wire Wire Line
	1700 2950 2350 2950
Text Label 4100 4650 0    50   ~ 0
RT_INT
Wire Wire Line
	3850 3950 4650 3950
Wire Wire Line
	4650 3950 4650 3050
Wire Wire Line
	4650 3050 5350 3050
Wire Wire Line
	3850 4050 4550 4050
Wire Wire Line
	4550 4050 4550 2950
Wire Wire Line
	4550 2950 5350 2950
Text Label 4100 3950 0    50   ~ 0
RxD
Text Label 4100 4050 0    50   ~ 0
TxD
$Comp
L power:GND #PWR0125
U 1 1 5E745B1A
P 5200 3150
F 0 "#PWR0125" H 5200 2900 50  0001 C CNN
F 1 "GND" V 5300 3100 50  0000 C CNN
F 2 "" H 5200 3150 50  0001 C CNN
F 3 "" H 5200 3150 50  0001 C CNN
	1    5200 3150
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0126
U 1 1 5E766F83
P 5050 3250
F 0 "#PWR0126" H 5050 3100 50  0001 C CNN
F 1 "+5V" V 5065 3378 50  0000 L CNN
F 2 "" H 5050 3250 50  0001 C CNN
F 3 "" H 5050 3250 50  0001 C CNN
	1    5050 3250
	0    -1   -1   0   
$EndComp
$Comp
L custom_library:ZS-040 U2
U 1 1 5E6E3A02
P 5450 2850
F 0 "U2" H 5122 2646 50  0000 R CNN
F 1 "ZS-040" H 5122 2555 50  0000 R CNN
F 2 "clock:zs-040" H 5450 2850 50  0001 C CNN
F 3 "" H 5450 2850 50  0001 C CNN
	1    5450 2850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5350 3150 5200 3150
Wire Wire Line
	5050 3250 5350 3250
$Comp
L Isolator:LTV-352T U3
U 1 1 5E43D3FC
P 12050 7700
F 0 "U3" H 12050 8025 50  0000 C CNN
F 1 "KPC452" H 12050 7934 50  0000 C CNN
F 2 "Package_SO:SO-4_4.4x3.6mm_P2.54mm" H 11750 7500 50  0001 L CIN
F 3 "http://optoelectronics.liteon.com/upload/download/DS70-2001-002/S_110_LTV-352T%2020140520.pdf" H 12050 7700 50  0001 L CNN
	1    12050 7700
	1    0    0    -1  
$EndComp
$Comp
L Isolator:LTV-352T U4
U 1 1 5E463235
P 12050 8250
F 0 "U4" H 12050 8575 50  0000 C CNN
F 1 "KPC452" H 12050 8484 50  0000 C CNN
F 2 "Package_SO:SO-4_4.4x3.6mm_P2.54mm" H 11750 8050 50  0001 L CIN
F 3 "http://optoelectronics.liteon.com/upload/download/DS70-2001-002/S_110_LTV-352T%2020140520.pdf" H 12050 8250 50  0001 L CNN
	1    12050 8250
	1    0    0    -1  
$EndComp
$Comp
L Isolator:LTV-352T U5
U 1 1 5E4654B1
P 12050 8800
F 0 "U5" H 12050 9125 50  0000 C CNN
F 1 "KPC452" H 12050 9034 50  0000 C CNN
F 2 "Package_SO:SO-4_4.4x3.6mm_P2.54mm" H 11750 8600 50  0001 L CIN
F 3 "http://optoelectronics.liteon.com/upload/download/DS70-2001-002/S_110_LTV-352T%2020140520.pdf" H 12050 8800 50  0001 L CNN
	1    12050 8800
	1    0    0    -1  
$EndComp
$Comp
L Isolator:LTV-352T U6
U 1 1 5E4663C0
P 12050 9350
F 0 "U6" H 12050 9675 50  0000 C CNN
F 1 "KPC452" H 12050 9584 50  0000 C CNN
F 2 "Package_SO:SO-4_4.4x3.6mm_P2.54mm" H 11750 9150 50  0001 L CIN
F 3 "http://optoelectronics.liteon.com/upload/download/DS70-2001-002/S_110_LTV-352T%2020140520.pdf" H 12050 9350 50  0001 L CNN
	1    12050 9350
	1    0    0    -1  
$EndComp
Connection ~ 13800 7150
Entry Wire Line
	13800 7500 13700 7600
Entry Wire Line
	13800 8050 13700 8150
Entry Wire Line
	13800 8600 13700 8700
Entry Wire Line
	13800 9150 13700 9250
Wire Wire Line
	13700 7600 12450 7600
Wire Wire Line
	12450 8150 13700 8150
Wire Wire Line
	13700 8700 12450 8700
Wire Wire Line
	12450 9250 13700 9250
Wire Wire Line
	12450 7800 12600 7800
Wire Wire Line
	12600 7800 12600 8350
Wire Wire Line
	12450 9450 12600 9450
Wire Wire Line
	12450 8900 12600 8900
Connection ~ 12600 8900
Wire Wire Line
	12600 8900 12600 9450
Wire Wire Line
	12450 8350 12600 8350
Connection ~ 12600 8350
Wire Wire Line
	12600 8350 12600 8900
Wire Wire Line
	12600 9600 12600 9450
Connection ~ 12600 9450
Wire Wire Line
	11650 7600 11450 7600
$Comp
L Device:R R17
U 1 1 5E70AB32
P 11300 7600
F 0 "R17" V 11100 7550 50  0000 L CNN
F 1 "2.2K" V 11200 7550 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 11230 7600 50  0001 C CNN
F 3 "~" H 11300 7600 50  0001 C CNN
	1    11300 7600
	0    1    1    0   
$EndComp
Wire Wire Line
	11650 8150 11450 8150
$Comp
L Device:R R18
U 1 1 5E76EEB7
P 11300 8150
F 0 "R18" V 11100 8100 50  0000 L CNN
F 1 "2.2K" V 11200 8100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 11230 8150 50  0001 C CNN
F 3 "~" H 11300 8150 50  0001 C CNN
	1    11300 8150
	0    1    1    0   
$EndComp
Wire Wire Line
	11650 8700 11450 8700
$Comp
L Device:R R19
U 1 1 5E78F653
P 11300 8700
F 0 "R19" V 11100 8650 50  0000 L CNN
F 1 "2.2K" V 11200 8650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 11230 8700 50  0001 C CNN
F 3 "~" H 11300 8700 50  0001 C CNN
	1    11300 8700
	0    1    1    0   
$EndComp
Wire Wire Line
	11650 9250 11450 9250
$Comp
L Device:R R20
U 1 1 5E7B0181
P 11300 9250
F 0 "R20" V 11100 9200 50  0000 L CNN
F 1 "2.2K" V 11200 9200 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 11230 9250 50  0001 C CNN
F 3 "~" H 11300 9250 50  0001 C CNN
	1    11300 9250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5E7D18FB
P 11550 9600
F 0 "#PWR0112" H 11550 9350 50  0001 C CNN
F 1 "GND" H 11555 9427 50  0000 C CNN
F 2 "" H 11550 9600 50  0001 C CNN
F 3 "" H 11550 9600 50  0001 C CNN
	1    11550 9600
	1    0    0    -1  
$EndComp
Wire Wire Line
	11650 7800 11550 7800
Wire Wire Line
	11550 7800 11550 8350
Wire Wire Line
	11650 9450 11550 9450
Connection ~ 11550 9450
Wire Wire Line
	11550 9450 11550 9600
Wire Wire Line
	11650 8900 11550 8900
Connection ~ 11550 8900
Wire Wire Line
	11550 8900 11550 9450
Wire Wire Line
	11650 8350 11550 8350
Connection ~ 11550 8350
Wire Wire Line
	11550 8350 11550 8900
Wire Bus Line
	5250 6800 10500 6800
Entry Wire Line
	13800 7000 13900 6900
Entry Wire Line
	13900 5400 13800 5500
Entry Wire Line
	10500 7500 10600 7600
Entry Wire Line
	10500 8050 10600 8150
Entry Wire Line
	10500 8600 10600 8700
Entry Wire Line
	10500 9150 10600 9250
Wire Wire Line
	11150 7600 10600 7600
Wire Wire Line
	11150 8150 10600 8150
Wire Wire Line
	10600 8700 11150 8700
Wire Wire Line
	11150 9250 10600 9250
Entry Wire Line
	5150 4450 5250 4550
Entry Wire Line
	5150 4550 5250 4650
Entry Wire Line
	5150 4850 5250 4950
Entry Wire Line
	5150 4750 5250 4850
Text Label 4750 4450 0    50   ~ 0
_1-.
Text Label 4750 4550 0    50   ~ 0
_2-.
Text Label 4750 4750 0    50   ~ 0
_3-.
Text Label 4750 4850 0    50   ~ 0
_4-.
Text Label 10750 7600 0    50   ~ 0
_1-.
Text Label 10750 8150 0    50   ~ 0
_2-.
Text Label 10750 8700 0    50   ~ 0
_3-.
Text Label 10750 9250 0    50   ~ 0
_4-.
Wire Wire Line
	11100 2100 11400 2100
Entry Wire Line
	11100 2100 11000 2200
Wire Wire Line
	11100 2300 11400 2300
Entry Wire Line
	11100 2300 11000 2400
Wire Wire Line
	11100 2400 11400 2400
Entry Wire Line
	11100 2400 11000 2500
Wire Wire Line
	11400 2500 11300 2500
Wire Wire Line
	11300 2500 11300 2550
Wire Wire Line
	11300 2550 10450 2550
Wire Wire Line
	10450 2550 10450 5400
Connection ~ 10450 5400
Wire Wire Line
	2350 6350 4400 6350
Wire Wire Line
	2350 2950 2350 6350
Wire Wire Line
	5500 4350 6000 4350
Wire Wire Line
	5150 4850 3850 4850
Wire Wire Line
	5150 4750 3850 4750
Wire Wire Line
	5150 4550 3850 4550
Wire Wire Line
	5150 4450 3850 4450
Wire Wire Line
	3850 4350 4650 4350
Wire Wire Line
	4650 4350 4650 8450
Connection ~ 4650 8450
Wire Wire Line
	3850 5250 5500 5250
Wire Wire Line
	5500 4350 5500 5250
Wire Wire Line
	5350 5500 5350 5150
Wire Wire Line
	5350 5150 3850 5150
Wire Wire Line
	5350 5500 10550 5500
Wire Wire Line
	5400 5400 5400 5050
Wire Wire Line
	5400 5050 3850 5050
Wire Wire Line
	5400 5400 10450 5400
Wire Wire Line
	5450 5300 5450 5000
Wire Wire Line
	5450 5000 5050 5000
Wire Wire Line
	5050 5000 5050 4950
Wire Wire Line
	5050 4950 3850 4950
Wire Wire Line
	5450 5300 10350 5300
Wire Wire Line
	3850 4650 4400 4650
Wire Wire Line
	4400 4650 4400 6350
Wire Wire Line
	10450 5750 11400 5750
Wire Bus Line
	10500 6800 10500 9750
Wire Bus Line
	13800 7150 13800 9550
Wire Bus Line
	5250 4300 5250 6800
Wire Bus Line
	11000 3750 11000 7150
Wire Bus Line
	12850 4700 12850 7150
Wire Bus Line
	11000 1500 11000 3750
Wire Bus Line
	12850 1450 12850 3750
Wire Bus Line
	13800 4450 13800 7150
Wire Bus Line
	13800 1200 13800 3750
$EndSCHEMATC
