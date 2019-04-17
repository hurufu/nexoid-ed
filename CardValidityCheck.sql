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
INSERT INTO diagrams VALUES(7,'Pre_Processing','-180 -125',NULL,75.0);
INSERT INTO diagrams VALUES(8,'Technology_Selection','0 0',NULL,75.0);
INSERT INTO diagrams VALUES(9,'Profile_Selection','0 0',NULL,75.0);
INSERT INTO diagrams VALUES(10,'Cvc_Check_Amount','0 -214',NULL,75.0);
INSERT INTO diagrams VALUES(11,'Kernel_Activation','0 0',NULL,75.0);
INSERT INTO diagrams VALUES(12,'Kernel_Processing','0 0',NULL,75.0);
INSERT INTO diagrams VALUES(13,'Outcome_Processing','0 0',NULL,75.0);
INSERT INTO diagrams VALUES(14,'Online_Request','0 0',NULL,75.0);
INSERT INTO diagrams VALUES(15,'Check_Online_Performed','0 0',NULL,75.0);
INSERT INTO diagrams VALUES(16,'Transaction_Completion','0 0',NULL,75.0);
INSERT INTO diagrams VALUES(17,'Card_Validity_Check','100 290',NULL,75.0);
CREATE TABLE state
(
	row integer primary key,
	current_dia integer,
	description text
);
INSERT INTO state VALUES(1,'',replace('=== h_header ===\n#include "Common.h"\n\n=== c_header ===\n#include <stdbool.h>','\n',char(10)));
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
INSERT INTO items VALUES(379,7,'beginend','Pre_Processing',0,170,60,70,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(380,7,'beginend','End',0,170,590,50,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(381,7,'vertical','',0,170,80,0,520,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(395,8,'beginend','Technology_Selection',0,170,60,90,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(396,8,'beginend','End',0,660,510,50,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(397,8,'vertical','',0,170,80,0,520,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(398,8,'vertical','',0,420,120,0,480,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(399,8,'vertical','',0,660,120,0,380,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(400,8,'horizontal','',0,170,120,490,0,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(401,8,'arrow','',0,20,120,150,480,400,1,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(402,8,'branch','branch 1',0,170,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(403,8,'address','branch 2',0,170,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(404,8,'branch','branch 2',0,420,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(405,8,'branch','branch 3',0,660,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(406,8,'address','branch 3',0,420,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(409,9,'beginend','Profile_Selection',0,170,60,80,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(410,9,'beginend','End',0,660,510,50,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(411,9,'vertical','',0,170,80,0,520,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(412,9,'vertical','',0,420,120,0,480,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(413,9,'vertical','',0,660,120,0,380,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(414,9,'horizontal','',0,170,120,490,0,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(415,9,'arrow','',0,20,120,150,480,400,1,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(416,9,'branch','branch 1',0,170,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(417,9,'address','branch 2',0,170,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(418,9,'branch','branch 2',0,420,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(419,9,'branch','branch 3',0,660,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(420,9,'address','branch 3',0,420,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(423,10,'beginend','Cvc_Check_Amount',0,160,70,80,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(424,10,'beginend','End',0,160,390,50,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(425,10,'vertical',NULL,0,160,70,0,310,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(428,11,'beginend','Kernel_Activation',0,170,60,80,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(429,11,'beginend','End',0,660,510,50,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(430,11,'vertical','',0,170,80,0,520,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(431,11,'vertical','',0,420,120,0,480,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(432,11,'vertical','',0,660,120,0,380,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(433,11,'horizontal','',0,170,120,490,0,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(434,11,'arrow','',0,20,120,150,480,400,1,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(435,11,'branch','branch 1',0,170,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(436,11,'address','branch 2',0,170,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(437,11,'branch','branch 2',0,420,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(438,11,'branch','branch 3',0,660,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(439,11,'address','branch 3',0,420,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(442,12,'beginend','Kernel_Processing',0,170,60,80,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(443,12,'beginend','End',0,660,510,50,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(444,12,'vertical','',0,170,80,0,520,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(445,12,'vertical','',0,420,120,0,480,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(446,12,'vertical','',0,660,120,0,380,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(447,12,'horizontal','',0,170,120,490,0,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(448,12,'arrow','',0,20,120,150,480,400,1,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(449,12,'branch','branch 1',0,170,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(450,12,'address','branch 2',0,170,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(451,12,'branch','branch 2',0,420,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(452,12,'branch','branch 3',0,660,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(453,12,'address','branch 3',0,420,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(456,13,'beginend','Outcome_Processing',0,170,60,90,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(457,13,'beginend','End',0,660,510,50,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(458,13,'vertical','',0,170,80,0,520,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(459,13,'vertical','',0,420,120,0,480,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(460,13,'vertical','',0,660,120,0,380,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(461,13,'horizontal','',0,170,120,490,0,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(462,13,'arrow','',0,20,120,150,480,400,1,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(463,13,'branch','branch 1',0,170,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(464,13,'address','branch 2',0,170,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(465,13,'branch','branch 2',0,420,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(466,13,'branch','branch 3',0,660,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(467,13,'address','branch 3',0,420,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(470,14,'beginend','Online_Request',0,170,60,70,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(471,14,'beginend','End',0,660,510,50,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(472,14,'vertical','',0,170,80,0,520,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(473,14,'vertical','',0,420,120,0,480,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(474,14,'vertical','',0,660,120,0,380,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(475,14,'horizontal','',0,170,120,490,0,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(476,14,'arrow','',0,20,120,150,480,400,1,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(477,14,'branch','branch 1',0,170,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(478,14,'address','branch 2',0,170,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(479,14,'branch','branch 2',0,420,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(480,14,'branch','branch 3',0,660,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(481,14,'address','branch 3',0,420,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(484,15,'beginend','Check_Online_Performed',0,170,60,100,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(485,15,'beginend','End',0,170,390,50,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(486,15,'vertical',NULL,0,170,80,0,290,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(489,16,'beginend','Transaction_Completion',0,170,60,100,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(490,16,'beginend','End',0,660,510,50,20,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(491,16,'vertical','',0,170,80,0,520,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(492,16,'vertical','',0,420,120,0,480,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(493,16,'vertical','',0,660,120,0,380,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(494,16,'horizontal','',0,170,120,490,0,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(495,16,'arrow','',0,20,120,150,480,400,1,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(496,16,'branch','branch 1',0,170,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(497,16,'address','branch 2',0,170,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(498,16,'branch','branch 2',0,420,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(499,16,'branch','branch 3',0,660,170,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(500,16,'address','branch 3',0,420,550,50,30,60,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(503,10,'if','tg_ctd->CvcDefaultAmount',0,160,140,120,20,130,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(504,10,'vertical','',0,410,140,0,150,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(505,10,'horizontal','',0,160,290,250,0,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(506,10,'shelf','*tg_ctd->CvcDefaultAmount',0,410,220,110,40,40,0,NULL,NULL,NULL,'tg_ctd->TransactionAmount');
INSERT INTO items VALUES(517,7,'if','tg_ctd->ServiceStartEvents.referenceEntry',0,170,250,190,20,40,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(518,7,'vertical','',0,400,250,0,250,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(520,7,'if','tg_ctd->SelectedService == S_NO_SHOW',0,400,310,170,20,30,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(521,7,'vertical','',0,600,310,0,190,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(523,7,'shelf','R_REFERENCE_ENTRY',0,400,420,170,40,40,0,NULL,NULL,NULL,'tg_ctd->Result');
INSERT INTO items VALUES(524,7,'horizontal','',0,170,500,430,0,0,0,NULL,NULL,NULL,NULL);
INSERT INTO items VALUES(525,17,'beginend','Card_Validity_Check',0,270,320,90,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(526,17,'beginend','End',0,4770,640,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(527,17,'vertical','',0,270,320,0,850,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(528,17,'vertical','',0,710,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(529,17,'vertical','',0,4770,390,0,250,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(530,17,'horizontal','',0,270,390,4500,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(531,17,'arrow','',0,110,390,160,780,4410,1,NULL,'',NULL,'');
INSERT INTO items VALUES(532,17,'branch','(A) Pre-Processing',0,270,440,110,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(533,17,'address',replace('(B) Tech\nSelection','\n',char(10)),0,270,1090,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(534,17,'branch',replace('(B) Tech\nSelection','\n',char(10)),0,710,450,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(535,17,'branch','(I) Completion',0,4770,440,110,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(536,17,'address',replace('(G) Non EMV\nchip based\nprocessing','\n',char(10)),0,710,1090,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(537,17,'horizontal','',0,270,320,270,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(538,17,'action','public',0,560,320,50,20,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(539,17,'branch',replace('(C) App Profile\nselection','\n',char(10)),0,1310,450,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(540,17,'branch',replace('(D) Kernel\nActivation','\n',char(10)),0,2220,450,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(541,17,'branch',replace('(E) Outcome\nProcessing','\n',char(10)),0,2670,450,160,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(542,17,'branch','(H) FAIL',0,4520,440,110,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(543,17,'vertical','',0,1310,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(544,17,'address',replace('(D) Kernel\nActivation','\n',char(10)),0,1310,1090,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(545,17,'address',replace('(B) Tech\nSelection','\n',char(10)),0,1630,1090,60,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(546,17,'address',replace('(E) Outcome\nProcessing','\n',char(10)),0,1800,1090,80,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(547,17,'address','(I) Completion',0,1970,1100,70,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(548,17,'insertion','Pre_Processing();',0,270,900,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(549,17,'if','tg_ctd->Result == R_OK',0,270,980,110,20,80,1,NULL,'',NULL,'');
INSERT INTO items VALUES(550,17,'vertical','',0,460,980,0,190,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(551,17,'address','(H) FAIL',0,460,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(552,17,'insertion','Technology_Selection();',0,710,800,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(553,17,'insertion','Profile_Selection();',0,1310,650,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(554,17,'select','tg_ctd->Result',0,1310,740,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(555,17,'horizontal','',0,1310,780,660,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(556,17,'case','R_OK',0,1310,820,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(557,17,'case','R_TAP_AGAIN',0,1630,820,60,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(558,17,'case','R_END_APPLICATION',0,1800,820,80,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(559,17,'vertical','',0,1630,780,0,390,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(560,17,'vertical','',0,1800,780,0,390,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(561,17,'case','',0,1970,820,70,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(562,17,'address',replace('(C) App Profile\nselection','\n',char(10)),0,1060,1090,70,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(563,17,'address','(H) FAIL',0,910,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(564,17,'vertical','',0,1970,780,0,390,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(565,17,'select','tg_ctd->Result',0,710,880,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(566,17,'horizontal','',0,710,930,350,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(567,17,'case','R_NON_EMV',0,710,970,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(568,17,'case','R_NOK',0,910,970,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(569,17,'case','',0,1060,970,70,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(570,17,'vertical','',0,910,930,0,240,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(571,17,'vertical','',0,1060,930,0,240,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(572,17,'branch',replace('(G) Non EMV\nchip based\nprocessing','\n',char(10)),0,4310,450,80,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(573,17,'insertion','Cvc_Check_Amount();',0,1310,890,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(574,17,'if','tg_ctd->Result == R_OK',0,1310,970,110,20,80,1,NULL,'',NULL,'');
INSERT INTO items VALUES(575,17,'vertical','',0,1500,970,0,200,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(576,17,'address','(H) FAIL',0,1500,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(577,17,'vertical','',0,2220,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(578,17,'insertion','Kernel_Activation();',0,2220,700,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(579,17,'if','tg_ctd->Result == R_OK',0,2220,770,110,20,80,1,NULL,'',NULL,'');
INSERT INTO items VALUES(580,17,'vertical','',0,2410,770,0,400,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(581,17,'address','(H) FAIL',0,2410,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(582,17,'address',replace('(E) Outcome\nProcessing','\n',char(10)),0,2220,1090,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(583,17,'insertion','Kernel_Processing();',0,2220,860,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(584,17,'if','tg_ctd->Result == R_OK',0,2220,930,110,20,80,1,NULL,'',NULL,'');
INSERT INTO items VALUES(585,17,'vertical','',0,2670,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(586,17,'insertion','Outcome_Processing();',0,2670,770,160,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(587,17,'if','tg_ctd->Outcome == O_ONLINE_REQUEST',0,2670,930,160,20,100,1,NULL,'',NULL,'');
INSERT INTO items VALUES(588,17,'vertical','',0,2930,930,0,240,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(589,17,'insertion','Online_Request();',0,3270,540,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(590,17,'if','tg_ctd->Result == R_OK',0,2670,850,160,20,250,1,NULL,'',NULL,'');
INSERT INTO items VALUES(591,17,'vertical','',0,3080,850,0,320,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(592,17,'select','tg_ctd->Out.Start',0,3270,720,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(593,17,'horizontal','',0,3270,760,770,0,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(594,17,'case','NONE',0,3270,800,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(595,17,'case','C',0,3760,800,70,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(596,17,'case','D',0,3920,800,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(597,17,'vertical','',0,3760,760,0,410,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(598,17,'vertical','',0,3920,760,0,410,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(599,17,'insertion','Check_Online_Performed();',0,3270,920,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(600,17,'if','tg_ctd->Result == R_OK',0,3270,990,110,20,80,1,NULL,'',NULL,'');
INSERT INTO items VALUES(601,17,'address','(I) Completion',0,3270,1100,110,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(602,17,'case','B',0,3600,800,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(603,17,'vertical','',0,3600,760,0,410,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(604,17,'address',replace('(B) Tech\nSelection','\n',char(10)),0,3600,1090,50,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(605,17,'address',replace('(C) App Profile\nselection','\n',char(10)),0,3760,1090,70,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(606,17,'address',replace('(D) Kernel\nActivation','\n',char(10)),0,3920,1090,50,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(607,17,'case','',0,4040,800,50,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(608,17,'vertical','',0,4040,760,0,410,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(609,17,'address','(H) FAIL',0,4040,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(610,17,'vertical','',0,4310,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(611,17,'vertical','',0,4520,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(612,17,'address','(H) FAIL',0,4310,1100,80,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(613,17,'address','(I) Completion',0,4520,1100,110,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(614,17,'address','(H) FAIL',0,3080,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(615,17,'shelf','T_ABORTED',0,4520,1010,110,40,40,0,NULL,'',NULL,'tg_ctd->TransactionResult');
INSERT INTO items VALUES(616,17,'insertion','Transaction_Completion();',0,4770,530,110,20,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(617,17,'commentout','120',0,4920,520,30,20,30,0,NULL,'',NULL,'');
INSERT INTO items VALUES(618,17,'commentin',replace('Non EMV is not\nsupported','\n',char(10)),0,4310,1000,80,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(619,17,'branch',replace('(F) Online Request\nProcessing','\n',char(10)),0,3270,450,110,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(620,17,'vertical','',0,3270,390,0,780,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(621,17,'address','(I) Completion',0,2670,1100,160,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(622,17,'address',replace('(F) Online Request\nProcessing','\n',char(10)),0,2930,1090,90,40,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(623,17,'if','tg_ctd->Result == R_OK',0,3270,600,110,20,780,1,NULL,'',NULL,'');
INSERT INTO items VALUES(624,17,'vertical','',0,3460,990,0,180,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(625,17,'vertical','',0,4160,600,0,570,0,0,NULL,'',NULL,'');
INSERT INTO items VALUES(626,17,'address','(H) FAIL',0,4160,1100,50,30,60,0,NULL,'',NULL,'');
INSERT INTO items VALUES(627,17,'address','(H) FAIL',0,3460,1100,50,30,60,0,NULL,'',NULL,'');
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
INSERT INTO tree_nodes VALUES(7,0,'item',NULL,7);
INSERT INTO tree_nodes VALUES(8,0,'item',NULL,8);
INSERT INTO tree_nodes VALUES(9,0,'item',NULL,9);
INSERT INTO tree_nodes VALUES(10,0,'item',NULL,10);
INSERT INTO tree_nodes VALUES(11,0,'item',NULL,11);
INSERT INTO tree_nodes VALUES(12,0,'item',NULL,12);
INSERT INTO tree_nodes VALUES(13,0,'item',NULL,13);
INSERT INTO tree_nodes VALUES(14,0,'item',NULL,14);
INSERT INTO tree_nodes VALUES(15,0,'item',NULL,15);
INSERT INTO tree_nodes VALUES(16,0,'item',NULL,16);
INSERT INTO tree_nodes VALUES(17,0,'folder','6.2 Service_Control',NULL);
INSERT INTO tree_nodes VALUES(18,17,'item',NULL,17);
CREATE INDEX items_per_diagram on items (diagram_id);
CREATE UNIQUE INDEX node_for_diagram on tree_nodes (diagram_id);
COMMIT;
