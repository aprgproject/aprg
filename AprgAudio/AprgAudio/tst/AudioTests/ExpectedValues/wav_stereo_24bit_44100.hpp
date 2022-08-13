#include <vector>

namespace wav_stereo_24bit_44100 {

int numSamplesPerChannel = 352800;
int bitDepth = 24;
int sampleRate = 44100;
int numChannels = 2;

std::vector<std::vector<double>> testBuffer = {
    {7.77244567871e-05, 0.000439882278442, 0.00674319267273,  0.0163820981979,   0.0151487588882,    0.00341582298279,     -0.0125023126602,  -0.0217453241348,  -0.0227074623108,  -0.0178270339966,  -0.000893712043762, 0.0107858181,
     0.00766479969025,  -0.00178730487823, -0.00629222393036, 0.00178396701813,  0.0313527584076,    0.0207730531693,
     -0.0222908258438,  0.00968170166016,  -0.00373435020447, -0.0470277070999,  0.0142315626144,    0.0251777172089,
     -0.00247633457184, 0.0208892822266,   -0.0109539031982,  -0.0392974615097,  -0.00938189029694,  -0.016600728035,
     -0.0539269447327,  -0.0511249303818,  0.0122632980347,   0.103702783585,    0.105173587799,     0.0613169670105,
     0.107999563217,    0.0264698266983,   -0.0883380174637,  -0.0407258272171,  -0.010347366333,    -0.00884878635406,
     0.0786321163177,   -0.0113770961761,  -0.0830408334732,  0.142681479454,    0.019171833992,     -0.0219069719315,
     0.024938583374,    -0.059695482254,   0.0529693365097,   -0.0265256166458,  0.0403858423233,    -0.00207006931305,
     0.0385066270828,   0.208563089371,    0.0995622873306,   0.171254515648,    0.149603962898,     0.139093875885,
     0.140897393227,    0.0962514877319,   0.049867272377,    0.0204880237579,   0.0566558837891,    0.0995980501175,
     0.0949305295944,   0.0366461277008,   0.118516087532,    0.0983523130417,   0.0982618331909,    0.0507235527039,
     0.003342628479,    -0.0649353265762,  -0.0789464712143,  0.00578963756561,  -0.0138659477234,   0.0213429927826,
     -0.0121517181396,  -0.00422608852386, -0.0278685092926,  0.0969288349152,   0.111292481422,     0.0508787631989,
     0.140943527222,    0.0854728221893,   0.0745220184326,   0.0653413534164,   0.118022322655,     0.0880781412125,
     0.0450122356415,   -0.00874435901642, -0.0475165843964,  0.0140289068222,   -0.0558882951736,   0.0301285982132,
     0.00447583198547,  -0.0438297986984,  0.0953339338303,   -0.0118364095688,  0.016367316246,     0.152486205101,
     0.108069062233,    0.162229537964,    0.10599386692,     0.0576605796814,   0.116208910942,     0.0424798727036,
     0.123232126236,    -0.00851690769196, -0.0378520488739,  0.0400956869125,   -0.0658235549927,   0.0411353111267,
     -0.0223900079727,  -0.0439848899841,  0.0252244472504,   0.0136346817017,   -0.0699175596237,   0.00593841075897,
     -0.0512816905975,  -0.155475139618,   -0.0383704900742,  -0.0644729137421,  -0.0632961988449,   0.0251125097275,
     0.0134855508804,   -0.158310890198,   -0.147775650024,   -0.0787174701691,  -0.00433027744293,  -0.0233926773071,
     -0.0288455486298,  -0.159164786339,   -0.170287847519,   -0.0726836919785,  -0.0306996107101,   0.048391699791,
     -0.132671713829,   -0.0565974712372,  -0.0780444145203,  -0.0725004673004,  -0.042083978653,    0.00945472717285,
     0.00442314147949,  -0.0782996416092,  0.121006965637,    0.105863451958,    0.136284589767,     0.080553650856,
     -0.0597985982895,  -0.0124866962433,  -0.0454322099686,  -0.030544757843,   -0.00940215587616,  -0.160868167877,
     -0.137446284294,   -0.134165644646,   -0.145178437233,   -0.0609300136566,  -0.0424057245255,   -0.0835481882095,
     -0.245255112648,   -0.203854560852,   -0.16884958744,    -0.170371294022,   -0.220833182335,    -0.173890471458,
     -0.0558353662491,  -0.0628813505173,  -0.00192093849182, -0.0594457387924,  -0.0382934808731,   0.00769698619843,
     0.0232107639313,   0.0633814334869,   0.0420830249786,   -0.0494782924652,  -0.058402299881,    -0.00989353656769,
     -0.0556210279465,  0.017005443573,    0.0575977563858,   0.0117911100388,   0.00971162319183,   0.0141184329987,
     0.0812700986862,   0.104591965675,    0.0341069698334,   0.115030050278,    0.103742837906,     0.0580484867096,
     0.161286115646,    0.135531067848,    0.0641927719116,   -0.0214301347733,  -0.0685315132141,   -0.0492191314697,
     -0.0864874124527,  -0.0943754911423,  0.00936710834503,  -0.118956446648,   -0.131529092789,    -0.0597389936447,
     -0.023782491684,   0.0938837528229,   -0.0816786289215,  -0.0495303869247,  -0.0222712755203,   0.0315406322479,
     0.0463569164276,   0.0305066108704,   -0.00937080383301, -0.143892407417,   -0.0515090227127,   -0.0487471818924,
     0.120163798332,    0.0870125293732,   0.0667072534561,   0.091993689537,    -0.0239210128784,   0.00293052196503,
     0.0205128192902,   -0.0126239061356,  -0.112153172493,   -0.132503151894,   -0.0756350755692,   0.168058037758,
     0.112046718597,    -0.0896764993668,  0.0186520814896,   -0.00146126747131, -0.0667836666107,   0.0946415662766,
     0.03679728508,     -0.131093502045,   -0.0767579078674,  -0.0292508602142,  0.028480887413,     0.0426660776138,
     0.125980377197,    0.206163287163,    0.132865905762,    0.0304782390594,   0.0914349555969,    0.0978326797485,
     0.0563305616379,   0.0616673231125,   0.0289442539215,   0.0885052680969,   0.105138063431,     0.146905303001,
     0.139025092125,    0.100531578064,    0.0745122432709,   0.147044301033,    0.0997745990753,    0.0872054100037,
     0.135490059853,    0.0318238735199,   0.0924507379532,   0.0496640205383,   0.0280466079712,    -0.00315356254578,
     0.0775496959686,   0.0921878814697,   0.0398114919662,   0.130702972412,    -0.0467922687531,   -0.0685148239136,
     0.0856246948242,   0.134173035622,    0.117228269577,    0.084511756897,    0.0773791074753,    0.0705616474152,
     0.047331571579,    0.0325963497162,   -0.0263532400131,  -0.0347250699997,  -0.013739824295,    -0.0967539548874,
     -0.0717287063599,  -0.0179476737976,  -0.0887115001678,  -0.121037244797,   0.00458216667175,   0.0286835432053,
     -0.00505411624908, -0.0312693119049,  0.00652635097504,  0.0846536159515,   -0.107051849365,    -0.204507231712,
     -0.152998328209,   -0.103457212448,   -0.104166865349,   -0.150072216988,   -0.105550527573,    -0.101711988449,
     -0.0448770523071,  0.0920099020004,   0.0859504938126,   0.0171504020691,   -0.0785477161407,   -0.154375195503,
     -0.0830782651901,  -0.0927363634109,  -0.0471074581146,  -0.0956993103027,  -0.145133018494,    -0.0601583719254,
     -0.0833103656769,  -0.0209926366806,  -0.0492763519287,  -0.0349304676056,  -0.0920147895813,   -0.192293524742,
     -0.111254811287,   -0.171246290207,   -0.165321350098,   -0.0884238481522,  -0.0922653675079,   -0.139559745789,
     -0.0894165039062,  -0.0810415744781,  -0.161728858948,   -0.0652614831924,  -0.0656758546829,   -0.0969500541687,
     -0.0874960422516,  -0.0550221204758,  -0.0248776674271,  -0.0100294351578,  0.0514001846313,    -0.0515828132629,
     -0.162224769592,   0.0138012170792,   0.213170528412,    0.160038113594,    0.0537011623383,    -0.0730376243591,
     -0.184214115143,   -0.152224779129,   -0.00570178031921, -0.00405919551849, 0.0977971553802,    0.190804839134,
     0.0834038257599,   0.0755777359009,   0.0666093826294,   0.0778206586838,   0.00162768363953,   0.0521218776703,
     -0.0630493164062,  -0.0710110664368,  0.283036470413,    0.234202265739,    0.115094184875,     0.070075750351,
     0.10632443428,     0.0932220220566,   -0.00922214984894, -0.077561378479,   -0.15642118454,     -0.154773235321,
     -0.228731274605,   -0.0907800197601,  -0.0197330713272,  -0.0730218887329,  0.0192404985428,    -0.0435231924057,
     -0.0899786949158,  -0.142906546593,   -0.171697258949,   0.00110614299774,  0.0418689250946,    -0.0351979732513,
     -0.150352835655,   -0.230516195297,   -0.123381018639,   -0.133100032806,   -0.0866953134537,   -0.0109071731567,
     0.092502951622,    0.326275587082,    0.363334298134,    0.319130182266,    0.29443192482,      0.15929710865,
     0.0383009910583,   0.134113311768,    0.261004567146,    0.23708152771,     -0.020155787468,    -0.13506937027,
     -0.0574617385864,  -0.0189056396484,  0.0511472225189,   0.131502628326,    0.0626163482666,    0.0357588529587,
     0.156155228615,    0.0648832321167,   0.13477408886,     0.193892478943,    0.163202643394,     0.0455857515335,
     -0.107415676117,   -0.0674904584885,  -0.0858421325684,  -0.167250394821,   -0.286704421043,    -0.218276619911,
     0.0656707286835,   0.311105132103,    0.28112244606,     0.222651362419,    0.0412223339081,    -0.0840843915939,
     -0.102630376816,   -0.154298186302,   -0.0205827951431,  -0.0893583297729,  -0.0821298360825,   0.00482511520386,
     0.0161000490189,   0.0871032476425,   0.122600197792,    0.17987537384,     0.0692788362503,    -0.00103902816772,
     0.045746922493,    0.0353325605392,   -0.00496387481689, -0.043234705925,   0.0951381921768,    0.0758788585663,
     -0.0360420942307,  -0.14196562767,    -0.133153915405,   0.0639377832413,   0.0827789306641,    0.0330204963684,
     -0.11815404892,    -0.101065278053,   0.0580755472183,   0.16034591198,     0.106783628464,     -0.00532388687134,
     0.0690177679062,   0.12052822113,     0.167081832886,    0.0130573511124,   -0.224110126495,    -0.323277950287,
     -0.346383452415,   -0.279021263123,   -0.195803761482,   -0.15061545372,    -0.130331397057,    -0.207055211067,
     -0.247290253639,   -0.260202288628,   -0.204931020737,   0.0256508588791,   -0.00347638130188,  -0.0690513849258,
     -0.0232795476913,  -0.0426096916199,  -0.0545936822891,  0.0778958797455,   0.0644354820251,    -0.0569397211075,
     0.00544500350952,  -0.0836207866669,  -0.167339920998,   -0.184236884117,   -0.0517193078995,   0.0333062410355,
     -0.0819302797318,  -0.119931459427,   -0.102344155312,   0.00610435009003,  0.074845790863,     -0.0507353544235,
     -0.0844293832779,  -0.0848418474197,  -0.150624632835,   -0.00802326202393, 0.0566700696945,    -0.00815367698669,
     -0.154028654099,   -0.202383875847,   -0.115745544434,   -0.082221865654,   -0.0145193338394,   0.0240012407303,
     0.0304847955704,   -0.109466314316},

    {0.000145316123962, 0.000302672386169, 0.00612282752991,   0.0153152942657,    0.0142148733139,   0.00587213039398,
     -0.00357162952423, -0.0115010738373,  -0.0217818021774,   -0.0234956741333,   -0.0021892786026,  0.00936055183411,
     0.00190007686615,  -0.0047607421875,  -0.00045371055603,  0.0112038850784,    0.0283315181732,   0.0117709636688,
     -0.0326575040817,  -0.00387370586395, -0.00323045253754,  -0.0545462369919,   0.00163185596466,  0.0433876514435,
     0.0187458992004,   0.0335485935211,   0.00750398635864,   -0.0354713201523,   -0.035783290863,   -0.0415679216385,
     -0.0326246023178,  -0.0796664953232,  0.00228583812714,   0.119603276253,     0.1707290411,      0.133585691452,
     0.101216077805,    0.123700022697,    0.0142438411713,    -0.0427062511444,   -0.00744879245758, 0.0219517946243,
     0.0263230800629,   0.0128881931305,   -0.0314878225327,   0.0151617527008,    0.0089875459671,   0.00101673603058,
     0.0396249294281,   -0.0273034572601,  0.00769448280334,   -0.0628191232681,   -0.0374784469604,  -0.051398396492,
     0.023775935173,    0.180346012115,    0.09792137146,      0.214262962341,     0.149571657181,    0.128116130829,
     0.241058707237,    0.143865942955,    0.047646522522,     0.0452275276184,    0.0312898159027,   0.0396672487259,
     0.0884878635406,   0.133904218674,    0.17617893219,      0.166540026665,     0.132598638535,    -0.00624084472656,
     0.00923895835876,  -0.100259542465,   -0.0875591039658,   -0.0276743173599,   -0.0538614988327,  -0.0149614810944,
     -0.132972836494,   -0.0495703220367,  -0.0948643684387,   -0.0460710525513,   0.0177819728851,   0.0304592847824,
     0.0292673110962,   0.0330222845078,   0.0660073757172,    0.0245407819748,    0.106195092201,    -0.0248200893402,
     0.0208106040955,   -0.0302308797836,  -0.119762301445,    -0.0557029247284,   -0.113383293152,   -0.047113776207,
     -0.016416311264,   0.0597515106201,   0.0276845693588,    0.0180337429047,    0.121524214745,    0.134414553642,
     0.113256812096,    0.107967734337,    0.122577667236,     0.0933433771133,    0.0372128486633,   -0.0533852577209,
     0.034006357193,    -0.0129648447037,  -0.0461241006851,   0.0369387865067,    -0.0290803909302,  -0.0243191719055,
     -0.0758582353592,  -0.119577765465,   -0.0275379419327,   -0.0585007667542,   -0.120086312294,   0.0264533758163,
     -0.0993094444275,  -0.149729609489,   -0.116085290909,    -0.0636162757874,   -0.0535707473755,  -0.0709199905396,
     0.026437163353,    -0.108775019646,   -0.102262735367,    -0.0210428237915,   0.0998295545578,   0.0804030895233,
     0.0579557418823,   -0.154113292694,   -0.120922446251,    -0.0384958982468,   -0.041912317276,   0.0977206230164,
     -0.12899017334,    -0.128626942635,   -0.105019807816,    0.0395255088806,    -0.044234752655,   -0.0160729885101,
     -0.0378762483597,  -0.111034989357,   0.110354661942,     0.0328115224838,    0.181324839592,    0.146373867989,
     0.0159071683884,   0.0135126113892,   0.0213625431061,    -0.01775431633,     -0.00308609008789, -0.0926826000214,
     -0.164421319962,   -0.0897985696793,  -0.151167035103,    -0.0410530567169,   -0.0322650671005,  -0.071456193924,
     -0.146623015404,   -0.133147239685,   -0.0646741390228,   -0.10977935791,     -0.182367682457,   -0.146279573441,
     -0.0404708385468,  0.0501581430435,   0.0361678600311,    -0.0060658454895,   0.0176256895065,   -0.0294834375381,
     0.0690938234329,   0.017613530159,    0.141121268272,     -0.000421404838562, -0.111880421638,   0.0959094762802,
     -0.0121730566025,  0.0264946222305,   0.064892411232,     0.07623898983,      0.0776113271713,   0.0477066040039,
     0.015567779541,    0.0996851921082,   0.00463199615479,   0.0276122093201,    0.0512830018997,   -0.0123369693756,
     0.1654702425,      0.127024888992,    0.166867494583,     -0.00233447551727,  -0.0578664541245,  0.0284008979797,
     0.0136790275574,   0.0576428174973,   0.0297405719757,    -0.0270335674286,   -0.0277284383774,  0.0568326711655,
     0.0629165172577,   0.147240281105,    0.0312472581863,    0.00281798839569,   0.0523567199707,   0.0575335025787,
     0.0277251005173,   0.036766409874,    -0.000621795654297, -0.118957519531,    -0.0755265951157,  -0.0956332683563,
     0.0577019453049,   0.125881791115,    0.148081660271,     0.0775977373123,    0.0388277769089,   -0.0566931962967,
     -0.0477006435394,  -0.0595755577087,  -0.167402505875,    -0.0499339103699,   -0.148880124092,   0.140307545662,
     0.146076321602,    -0.0367206335068,  -0.010816693306,    -0.0592707395554,   0.0505766868591,   0.095737695694,
     0.0616101026535,   -0.123353123665,   -0.158329486847,    -0.0854361057281,   0.0250186920166,   0.0498366355896,
     0.114591956139,    0.136102199554,    0.0695546865463,    0.0844231843948,    0.0423127412796,   0.075180888176,
     0.0477529764175,   0.00923907756805,  0.012347817421,     0.0741232633591,    0.0449873209,      0.0521856546402,
     0.0561290979385,   0.0160149335861,   0.00930082798004,   0.0112993717194,    -0.0263483524323,  -0.0799117088318,
     0.00456082820892,  -0.0725563764572,  -0.0662146806717,   -0.0694227218628,   -0.111401796341,   -0.0777508020401,
     -0.0115401744843,  0.0222812891006,   -0.0217269659042,   -0.00717294216156,  -0.127527475357,   -0.15928196907,
     -0.0219542980194,  0.0617127418518,   0.0245968103409,    0.0226804018021,    0.0147042274475,   -0.0437377691269,
     -0.0460163354874,  -0.0243554115295,  -0.0463002920151,   -0.0449978113174,   -0.0101661682129,  -0.0465919971466,
     -0.066002368927,   -0.118350863457,   -0.137733221054,    -0.166067242622,    -0.0891143083572,  0.000721335411072,
     -0.0293145179749,  -0.0378077030182,  -0.00143432617188,  0.0738503932953,    -0.109228014946,   -0.178063750267,
     -0.114200472832,   -0.0551174879074,  -0.0126582384109,   -0.143907308578,    -0.0699659585953,  -0.023008108139,
     0.00907254219055,  0.142829656601,    0.051952958107,     -0.0592143535614,   -0.127992391586,   -0.185090184212,
     -0.0928454399109,  -0.0624305009842,  -0.0205240249634,   -0.0354903936386,   -0.067312002182,   -0.00700664520264,
     -0.0338667631149,  0.0183874368668,   0.0207358598709,    0.0653097629547,    0.00133633613586,  -0.0908387899399,
     -0.0562492609024,  -0.0769830942154,  -0.016828417778,    -0.00967609882355,  0.0411602258682,   -0.0366946458817,
     -0.0410319566727,  0.0309782028198,   0.0392956733704,    0.0669734477997,    0.018067240715,    0.0463429689407,
     0.0312809944153,   0.0550159215927,   0.0195442438126,    0.0729103088379,    0.0478173494339,   -0.0789768695831,
     -0.0462082624435,  0.157876610756,    0.214052915573,     0.134649395943,     0.235051512718,    0.145732522011,
     0.188170313835,    0.191153287888,    0.0713073015213,    -0.0558511018753,   0.0889047384262,   0.243727087975,
     0.0652730464935,   -0.0260493755341,  -0.192010045052,    -0.188719749451,    -0.123023152351,   -0.15177500248,
     -0.173936724663,   -0.0367410182953,  0.0120911598206,    0.0948275327682,    0.197672367096,    0.128889679909,
     0.0591852664948,   -0.176646709442,   -0.145018577576,    -0.0598595142365,   0.0713049173355,   0.200659871101,
     0.161377072334,    0.161349415779,    0.160175204277,     0.218865633011,     0.074162364006,    0.000883817672729,
     0.0207576751709,   -0.0812919139862,  0.0727087259293,    0.241757035255,     0.137862443924,    -0.0446484088898,
     0.0130958557129,   0.201958417892,    0.00947666168213,   -0.146315097809,    -0.185536384583,   -0.0361466407776,
     0.143862962723,    0.00547909736633,  0.0646140575409,    0.146261930466,     0.114366054535,    -0.13300037384,
     -0.171762228012,   -0.0333876609802,  -0.00815165042877,  0.0873540639877,    -0.0235226154327,  -0.0686619281769,
     -0.086855173111,   -0.10927093029,    -0.0432237386703,   0.101382732391,     0.142577409744,    0.0554286241531,
     -0.0758368968964,  -0.144561767578,   -0.00560939311981,  -0.0810438394547,   -0.14150249958,    -0.155748844147,
     -0.197823762894,   -0.172927260399,   -0.0387709140778,   0.0862083435059,    -0.070552110672,   -0.153396248817,
     -0.0289398431778,  0.0802103281021,   0.031609416008,     0.00658047199249,   0.0768996477127,   0.215312957764,
     0.161543726921,    0.0448981523514,   0.00625360012054,   -0.198372840881,    -0.215194940567,   -0.170367717743,
     -0.0762928724289,  0.015300154686,    -0.061603307724,    -0.078665971756,    -0.162214398384,   -0.144822359085,
     -0.0914835929871,  -0.149238109589,   -0.0255004167557,   -0.0604685544968,   -0.221594214439,   -0.110464215279,
     -0.00390541553497, 0.0703004598618,   0.00940084457397,   -0.0397210121155,   -0.100506544113,   -0.135923862457,
     -0.0912399291992,  -0.143422722816,   -0.0174454450607,   -0.00703489780426,  -0.139353871346,   -0.240300297737,
     -0.113995790482,   -0.0422520637512,  0.120814561844,     0.117279529572,     -0.0794944763184,  0.0266873836517,
     -0.0561690330505,  0.0189610719681,   -0.0162931680679,   0.101825237274,     0.0976914167404,   -0.0173678398132,
     -0.0139818191528,  -0.155893802643,   0.0232023000717,    0.0571312904358,    0.10260951519,     0.00437140464783,
     -0.0616220235825,  -0.106693029404,   -0.0611317157745,   -0.00502419471741,  -0.0499160289764,  0.0248484611511,
     -0.0620601177216,  -0.052773475647,   -0.210844993591,    -0.116495132446,    0.0130721330643,   0.0545973777771,
     0.00759077072144,  -0.102944374084,   0.0247064828873,    0.0107057094574,    0.104310154915,    0.0161085128784,
     0.0211653709412,   0.032613992691,    0.0314596891403,    0.113596200943,     0.080953001976,    0.0768167972565,
     -0.012017250061,   -0.0764977931976,  -0.182181358337,    -0.0493264198303,   0.0212137699127,   0.139509081841,
     0.235778927803,    0.0965129137039}};

}  // namespace wav_stereo_24bit_44100
