PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE info
		(
			key text primary key,
			value text
		);
INSERT INTO info VALUES('type','drakon');
INSERT INTO info VALUES('version','31');
INSERT INTO info VALUES('start_version','1');
INSERT INTO info VALUES('language','C');
CREATE TABLE diagrams
(
	diagram_id integer primary key,
	name text unique,
	origin text,
	description text,
	zoom double
);
INSERT INTO diagrams VALUES(18,'Card_Validity_Check','100 290','CVC',75.0);
INSERT INTO diagrams VALUES(19,'Online_Request','0 0','',75.0);
INSERT INTO diagrams VALUES(20,'Transaction_Completion','0 0','',75.0);
INSERT INTO diagrams VALUES(21,'Cvc_Check_Amount','0 -214','',75.0);
INSERT INTO diagrams VALUES(22,'Check_Online_Performed','0 0','',75.0);
INSERT INTO diagrams VALUES(25,'Kernel_Activation','0 0','',75.0);
INSERT INTO diagrams VALUES(26,'Profile_Selection','0 0','',75.0);
INSERT INTO diagrams VALUES(27,'Kernel_Processing','0 0','',75.0);
INSERT INTO diagrams VALUES(28,'Outcome_Processing','0 0','',75.0);
INSERT INTO diagrams VALUES(29,'Pre_Processing','-180 -125','',75.0);
INSERT INTO diagrams VALUES(30,'Technology_Selection','0 0','',75.0);
CREATE TABLE state
(
	row integer primary key,
	current_dia integer,
	description text
);
INSERT INTO state VALUES(1,18,replace('=== h_header ===\n#include "Common.h"\n\n=== c_header ===\n#include <stdbool.h>','\n',char(10)));
CREATE TABLE items
(
	item_id integer primary key,
	diagram_id integer,
	type text,
	text text,
	selected integer,
	x integer,
	y integer,
	w integer,
	h integer,
	a integer,
	b integer,
	aux_value integer,
	color text,
	format text,
	text2 text
);
INSERT INTO items VALUES(628,18,'beginend','Card_Validity_Check',0,270,320,90,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(629,18,'beginend','End',0,4770,640,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(630,18,'vertical','',0,270,320,0,850,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(631,18,'vertical','',0,700,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(632,18,'vertical','',0,4770,390,0,250,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(633,18,'horizontal','',0,270,390,4500,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(634,18,'arrow','',0,110,390,160,780,4410,1,NULL,'',NULL,'');
INSERT INTO items VALUES(635,18,'branch','(A) Pre-Processing',0,270,440,110,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(636,18,'address',replace('(B) Tech\nSelection','\n',char(10)),0,270,1090,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(637,18,'branch',replace('(B) Tech\nSelection','\n',char(10)),0,700,450,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(638,18,'branch','(I) Completion',0,4770,440,110,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(639,18,'address',replace('(G) Non EMV\nchip based\nprocessing','\n',char(10)),0,700,1090,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(640,18,'horizontal','',0,270,320,270,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(641,18,'action','public',0,560,320,50,20,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(642,18,'branch',replace('(C) App Profile\nselection','\n',char(10)),0,1310,450,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(643,18,'branch',replace('(D) Kernel\nActivation','\n',char(10)),0,2220,450,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(644,18,'branch',replace('(E) Outcome\nProcessing','\n',char(10)),0,2670,450,160,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(645,18,'branch','(H) FAIL',0,4520,440,110,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(646,18,'vertical','',0,1310,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(647,18,'address',replace('(D) Kernel\nActivation','\n',char(10)),0,1310,1090,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(648,18,'address',replace('(B) Tech\nSelection','\n',char(10)),0,1630,1090,60,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(649,18,'address',replace('(E) Outcome\nProcessing','\n',char(10)),0,1800,1090,80,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(650,18,'address','(I) Completion',0,1970,1100,70,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(651,18,'insertion','Pre_Processing();',0,270,900,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(652,18,'if','tg_ctd->Result == R_OK',0,270,980,110,20,80,1,NULL,'',NULL,'');
INSERT INTO items VALUES(653,18,'vertical','',0,460,980,0,190,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(654,18,'address','(H) FAIL',0,460,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(655,18,'insertion','Technology_Selection();',0,700,800,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(656,18,'insertion','Profile_Selection();',0,1310,650,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(657,18,'select','tg_ctd->Result',0,1310,740,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(658,18,'horizontal','',0,1310,780,660,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(659,18,'case','R_OK',0,1310,820,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(660,18,'case','R_TAP_AGAIN',0,1630,820,60,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(661,18,'case','R_END_APPLICATION',0,1800,820,80,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(662,18,'vertical','',0,1630,780,0,390,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(663,18,'vertical','',0,1800,780,0,390,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(664,18,'case','',0,1970,820,70,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(665,18,'address',replace('(C) App Profile\nselection','\n',char(10)),0,1060,1090,70,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(666,18,'address','(H) FAIL',0,910,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(667,18,'vertical','',0,1970,780,0,390,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(668,18,'select','tg_ctd->Result',0,700,880,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(669,18,'horizontal','',0,700,930,360,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(670,18,'case','R_NON_EMV',0,700,970,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(671,18,'case','R_NOK',0,910,970,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(672,18,'case','',0,1060,970,70,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(673,18,'vertical','',0,910,930,0,240,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(674,18,'vertical','',0,1060,930,0,240,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(675,18,'branch',replace('(G) Non EMV\nchip based\nprocessing','\n',char(10)),0,4310,450,80,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(676,18,'insertion','Cvc_Check_Amount();',0,1310,890,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(677,18,'if','tg_ctd->Result == R_OK',0,1310,970,110,20,80,1,NULL,'',NULL,'');
INSERT INTO items VALUES(678,18,'vertical','',0,1500,970,0,200,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(679,18,'address','(H) FAIL',0,1500,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(680,18,'vertical','',0,2220,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(681,18,'insertion','Kernel_Activation();',0,2220,700,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(682,18,'if','tg_ctd->Result == R_OK',0,2220,770,110,20,80,1,NULL,'',NULL,'');
INSERT INTO items VALUES(683,18,'vertical','',0,2410,770,0,400,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(684,18,'address','(H) FAIL',0,2410,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(685,18,'address',replace('(E) Outcome\nProcessing','\n',char(10)),0,2220,1090,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(686,18,'insertion','Kernel_Processing();',0,2220,860,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(687,18,'if','tg_ctd->Result == R_OK',0,2220,930,110,20,80,1,NULL,'',NULL,'');
INSERT INTO items VALUES(688,18,'vertical','',0,2670,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(689,18,'insertion','Outcome_Processing();',0,2670,770,160,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(690,18,'if','tg_ctd->Outcome == O_ONLINE_REQUEST',0,2670,930,160,20,100,1,NULL,'',NULL,'');
INSERT INTO items VALUES(691,18,'vertical','',0,2930,930,0,240,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(692,18,'insertion','Online_Request();',0,3270,540,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(693,18,'if','tg_ctd->Result == R_OK',0,2670,850,160,20,250,1,NULL,'',NULL,'');
INSERT INTO items VALUES(694,18,'vertical','',0,3080,850,0,320,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(695,18,'select','tg_ctd->Out.Start',0,3270,720,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(696,18,'horizontal','',0,3270,760,770,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(697,18,'case','NONE',0,3270,800,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(698,18,'case','C',0,3760,800,70,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(699,18,'case','D',0,3920,800,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(700,18,'vertical','',0,3760,760,0,410,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(701,18,'vertical','',0,3920,760,0,410,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(702,18,'insertion','Check_Online_Performed();',0,3270,920,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(703,18,'if','tg_ctd->Result == R_OK',0,3270,990,110,20,80,1,NULL,'',NULL,'');
INSERT INTO items VALUES(704,18,'address','(I) Completion',0,3270,1100,110,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(705,18,'case','B',0,3600,800,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(706,18,'vertical','',0,3600,760,0,410,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(707,18,'address',replace('(B) Tech\nSelection','\n',char(10)),0,3600,1090,50,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(708,18,'address',replace('(C) App Profile\nselection','\n',char(10)),0,3760,1090,70,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(709,18,'address',replace('(D) Kernel\nActivation','\n',char(10)),0,3920,1090,50,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(710,18,'case','',0,4040,800,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(711,18,'vertical','',0,4040,760,0,410,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(712,18,'address','(H) FAIL',0,4040,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(713,18,'vertical','',0,4310,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(714,18,'vertical','',0,4520,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(715,18,'address','(H) FAIL',0,4310,1100,80,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(716,18,'address','(I) Completion',0,4520,1100,110,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(717,18,'address','(H) FAIL',0,3080,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(718,18,'shelf','T_ABORTED',0,4520,1010,110,40,40,0,NULL,'',NULL,'tg_ctd->TransactionResult');
INSERT INTO items VALUES(719,18,'insertion','Transaction_Completion();',0,4770,530,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(720,18,'commentout','120',0,4920,520,30,20,30,0,NULL,'',NULL,'');
INSERT INTO items VALUES(721,18,'commentin',replace('Non EMV is not\nsupported','\n',char(10)),0,4310,1000,80,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(722,18,'branch',replace('(F) Online Request\nProcessing','\n',char(10)),0,3270,450,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(723,18,'vertical','',0,3270,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(724,18,'address','(I) Completion',0,2670,1100,160,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(725,18,'address',replace('(F) Online Request\nProcessing','\n',char(10)),0,2930,1090,90,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(726,18,'if','tg_ctd->Result == R_OK',0,3270,600,110,20,780,1,NULL,'',NULL,'');
INSERT INTO items VALUES(727,18,'vertical','',0,3460,990,0,180,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(728,18,'vertical','',0,4160,600,0,570,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(729,18,'address','(H) FAIL',0,4160,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(730,18,'address','(H) FAIL',0,3460,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(731,19,'beginend','Online_Request',0,170,60,70,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(732,19,'beginend','End',0,660,510,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(733,19,'vertical','',0,170,80,0,520,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(734,19,'vertical','',0,420,120,0,480,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(735,19,'vertical','',0,660,120,0,380,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(736,19,'horizontal','',0,170,120,490,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(737,19,'arrow','',0,20,120,150,480,400,1,NULL,'',NULL,'');
INSERT INTO items VALUES(738,19,'branch','branch 1',0,170,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(739,19,'address','branch 2',0,170,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(740,19,'branch','branch 2',0,420,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(741,19,'branch','branch 3',0,660,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(742,19,'address','branch 3',0,420,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(743,20,'beginend','Transaction_Completion',0,170,60,100,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(744,20,'beginend','End',0,660,510,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(745,20,'vertical','',0,170,80,0,520,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(746,20,'vertical','',0,420,120,0,480,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(747,20,'vertical','',0,660,120,0,380,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(748,20,'horizontal','',0,170,120,490,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(749,20,'arrow','',0,20,120,150,480,400,1,NULL,'',NULL,'');
INSERT INTO items VALUES(750,20,'branch','branch 1',0,170,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(751,20,'address','branch 2',0,170,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(752,20,'branch','branch 2',0,420,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(753,20,'branch','branch 3',0,660,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(754,20,'address','branch 3',0,420,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(755,21,'beginend','Cvc_Check_Amount',0,160,70,80,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(756,21,'beginend','End',0,160,390,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(757,21,'vertical','',0,160,70,0,310,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(758,21,'if','tg_ctd->CvcDefaultAmount',0,160,140,120,20,130,0,NULL,'',NULL,'');
INSERT INTO items VALUES(759,21,'vertical','',0,410,140,0,150,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(760,21,'horizontal','',0,160,290,250,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(761,21,'shelf','*tg_ctd->CvcDefaultAmount',0,410,220,110,40,40,0,NULL,'',NULL,'tg_ctd->TransactionAmount');
INSERT INTO items VALUES(762,22,'beginend','Check_Online_Performed',0,170,60,100,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(763,22,'beginend','End',0,170,390,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(764,22,'vertical','',0,170,80,0,290,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(786,25,'beginend','Kernel_Activation',0,170,60,80,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(787,25,'beginend','End',0,660,510,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(788,25,'vertical','',0,170,80,0,520,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(789,25,'vertical','',0,420,120,0,480,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(790,25,'vertical','',0,660,120,0,380,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(791,25,'horizontal','',0,170,120,490,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(792,25,'arrow','',0,20,120,150,480,400,1,NULL,'',NULL,'');
INSERT INTO items VALUES(793,25,'branch','branch 1',0,170,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(794,25,'address','branch 2',0,170,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(795,25,'branch','branch 2',0,420,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(796,25,'branch','branch 3',0,660,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(797,25,'address','branch 3',0,420,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(798,26,'beginend','Profile_Selection',0,170,60,80,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(799,26,'beginend','End',0,660,510,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(800,26,'vertical','',0,170,80,0,520,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(801,26,'vertical','',0,420,120,0,480,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(802,26,'vertical','',0,660,120,0,380,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(803,26,'horizontal','',0,170,120,490,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(804,26,'arrow','',0,20,120,150,480,400,1,NULL,'',NULL,'');
INSERT INTO items VALUES(805,26,'branch','branch 1',0,170,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(806,26,'address','branch 2',0,170,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(807,26,'branch','branch 2',0,420,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(808,26,'branch','branch 3',0,660,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(809,26,'address','branch 3',0,420,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(810,27,'beginend','Kernel_Processing',0,170,60,80,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(811,27,'beginend','End',0,660,510,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(812,27,'vertical','',0,170,80,0,520,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(813,27,'vertical','',0,420,120,0,480,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(814,27,'vertical','',0,660,120,0,380,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(815,27,'horizontal','',0,170,120,490,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(816,27,'arrow','',0,20,120,150,480,400,1,NULL,'',NULL,'');
INSERT INTO items VALUES(817,27,'branch','branch 1',0,170,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(818,27,'address','branch 2',0,170,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(819,27,'branch','branch 2',0,420,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(820,27,'branch','branch 3',0,660,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(821,27,'address','branch 3',0,420,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(822,28,'beginend','Outcome_Processing',0,170,60,90,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(823,28,'beginend','End',0,660,510,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(824,28,'vertical','',0,170,80,0,520,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(825,28,'vertical','',0,420,120,0,480,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(826,28,'vertical','',0,660,120,0,380,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(827,28,'horizontal','',0,170,120,490,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(828,28,'arrow','',0,20,120,150,480,400,1,NULL,'',NULL,'');
INSERT INTO items VALUES(829,28,'branch','branch 1',0,170,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(830,28,'address','branch 2',0,170,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(831,28,'branch','branch 2',0,420,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(832,28,'branch','branch 3',0,660,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(833,28,'address','branch 3',0,420,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(834,29,'beginend','Pre_Processing',0,170,60,70,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(835,29,'beginend','End',0,170,590,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(836,29,'vertical','',0,170,80,0,520,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(837,29,'if','tg_ctd->ServiceStartEvents.referenceEntry',0,170,250,190,20,40,0,NULL,'',NULL,'');
INSERT INTO items VALUES(838,29,'vertical','',0,400,250,0,250,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(839,29,'if','tg_ctd->SelectedService == S_NO_SHOW',0,400,310,170,20,30,0,NULL,'',NULL,'');
INSERT INTO items VALUES(840,29,'vertical','',0,600,310,0,190,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(841,29,'shelf','R_REFERENCE_ENTRY',0,400,420,170,40,40,0,NULL,'',NULL,'tg_ctd->Result');
INSERT INTO items VALUES(842,29,'horizontal','',0,170,500,430,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(843,30,'beginend','Technology_Selection',0,170,60,90,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(844,30,'beginend','End',0,660,510,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(845,30,'vertical','',0,170,80,0,520,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(846,30,'vertical','',0,420,120,0,480,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(847,30,'vertical','',0,660,120,0,380,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(848,30,'horizontal','',0,170,120,490,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(849,30,'arrow','',0,20,120,150,480,400,1,NULL,'',NULL,'');
INSERT INTO items VALUES(850,30,'branch','branch 1',0,170,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(851,30,'address','branch 2',0,170,550,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(852,30,'branch','branch 2',0,420,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(853,30,'branch','branch 3',0,660,170,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(854,30,'address','branch 3',0,420,550,50,30,60,0,NULL,'',NULL,'');
CREATE TABLE diagram_info
(
	diagram_id integer,
	name text,
	value text,
	primary key (diagram_id, name)
);
CREATE TABLE tree_nodes
(
	node_id integer primary key,
	parent integer,
	type text,
	name text,
	diagram_id integer
);
INSERT INTO tree_nodes VALUES(19,0,'folder','06 Card Service Processing',NULL);
INSERT INTO tree_nodes VALUES(22,19,'folder','6.2 Service_Control',NULL);
INSERT INTO tree_nodes VALUES(23,22,'item','',18);
INSERT INTO tree_nodes VALUES(24,0,'folder','05 Terminal and Card Initiation',NULL);
INSERT INTO tree_nodes VALUES(25,19,'folder','6.3 Online Request Outcome Processing',NULL);
INSERT INTO tree_nodes VALUES(26,25,'item','',19);
INSERT INTO tree_nodes VALUES(27,19,'folder','6.4 Transaction Completion',NULL);
INSERT INTO tree_nodes VALUES(28,27,'item','',20);
INSERT INTO tree_nodes VALUES(29,19,'folder','6.5 Data Exchange Processing',NULL);
INSERT INTO tree_nodes VALUES(30,19,'folder','6.6 Service Supporting Functions',NULL);
INSERT INTO tree_nodes VALUES(31,30,'item','',21);
INSERT INTO tree_nodes VALUES(32,30,'item','',22);
INSERT INTO tree_nodes VALUES(33,19,'folder','6.7 UI Request Processing',NULL);
INSERT INTO tree_nodes VALUES(34,0,'folder','07 Card Interaction Layer',NULL);
INSERT INTO tree_nodes VALUES(39,34,'item','',25);
INSERT INTO tree_nodes VALUES(40,34,'item','',26);
INSERT INTO tree_nodes VALUES(41,34,'item','',27);
INSERT INTO tree_nodes VALUES(42,34,'item','',28);
INSERT INTO tree_nodes VALUES(43,34,'item','',29);
INSERT INTO tree_nodes VALUES(44,34,'item','',30);
INSERT INTO tree_nodes VALUES(45,0,'folder','08 Kernel E Processing',NULL);
INSERT INTO tree_nodes VALUES(46,0,'folder','09 Kernel M Processing',NULL);
INSERT INTO tree_nodes VALUES(47,0,'folder','11 Supporting Functions',NULL);
CREATE INDEX items_per_diagram on items (diagram_id);
CREATE UNIQUE INDEX node_for_diagram on tree_nodes (diagram_id);
COMMIT;
