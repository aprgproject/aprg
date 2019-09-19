#include <vector>

namespace wav_stereo_24bit_48000 { 

int numSamplesPerChannel = 384000;
int bitDepth = 24;
int sampleRate = 48000;
int numChannels = 2;

std::vector<std::vector<double>> testBuffer = {{-0.000535368919373, -0.00181579589844, -0.00248157978058, -0.00175869464874, -0.000969409942627, -0.000530123710632, -0.000239849090576, -0.00066339969635, -0.000734448432922, 0.00139260292053, 0.00468695163727, 0.00530195236206, 0.00144791603088, -0.00350785255432, -0.00509893894196, -0.00236320495605, 0.00193166732788, 0.00389695167542, 0.00217139720917, -0.000704765319824, -0.00144803524017, -0.000849843025208, -0.00170028209686, -0.00326788425446, -0.00386130809784, -0.00107598304749, 0.0118240118027, 0.0278670787811, 0.0185575485229, -0.0169941186905, -0.0355042219162, -0.0214304924011, -0.000935912132263, 0.018381357193, 0.0288296937943, 0.00724148750305, -0.0189445018768, -0.00481104850769, 0.0188766717911, 0.00283479690552, -0.0235620737076, -0.00899910926819, 0.0164365768433, 0.00385200977325, -0.00245523452759, 0.0333852767944, 0.0402925014496, -0.00783336162567, -0.031529545784, -0.00864863395691, 0.0105214118958, 0.0214656591415, 0.0276129245758, -0.00490951538086, -0.0415140390396, -0.000699996948242, 0.0718402862549, 0.05355656147, -0.0389492511749, -0.0694912672043, -0.000436782836914, 0.0593814849854, 0.03382563591, -0.0216007232666, -0.0245040655136, 0.0183376073837, 0.0350197553635, 0.00948882102966, -0.00254774093628, 0.00548541545868, -0.00484228134155, -0.0105837583542, 0.0137873888016, 0.0166019201279, -0.0180323123932, -0.0213668346405, 0.0169984102249, 0.0301740169525, 0.00754773616791, -0.00407469272614, 0.00835728645325, 0.0148799419403, -0.00720882415771, -0.0260472297668, 0.00359523296356, 0.0419363975525, 0.0174108743668, -0.0407017469406, -0.0440566539764, 0.017639040947, 0.0573456287384, 0.0120804309845, -0.0530525445938, -0.0338799953461, 0.0451798439026, 0.0642675161362, 0.00221788883209, -0.023540019989, 0.032926440239, 0.041263461113, -0.0441994667053, -0.0586806535721, 0.0303201675415, 0.0523092746735, 0.00276637077332, -0.00232934951782, 0.0101647377014, 0.00439178943634, 0.00419509410858, -0.00891280174255, -0.0140097141266, 0.00794851779938, -0.0181781053543, -0.0613112449646, 0.00252866744995, 0.0917369127274, 0.04485476017, -0.058807849884, -0.0595812797546, 0.000520467758179, 0.00566327571869, -0.0249289274216, -0.0235843658447, -0.00893819332123, -0.0188995599747, -0.0217773914337, 0.0110683441162, 0.0272953510284, -0.0112103223801, -0.0515877008438, -0.05326628685, -0.0392282009125, -0.0149552822113, 0.0223093032837, 0.0210065841675, -0.033660531044, -0.0508046150208, 0.0123757123947, 0.0774039030075, 0.0862331390381, 0.0492680072784, -0.0203523635864, -0.101112008095, -0.140402555466, -0.103650689125, -0.0232540369034, 0.0385713577271, 0.0543519258499, 0.0388987064362, 0.0128527879715, -0.0309870243073, -0.0892986059189, -0.0982472896576, -0.0326007604599, 0.0306036472321, 0.0515545606613, 0.0559309720993, 0.0303671360016, -0.0249246358871, -0.0509266853333, -0.0245321989059, 0.011846780777, 0.0132650136948, -0.00581967830658, 0.00267124176025, 0.00760173797607, -0.0393438339233, -0.0431913137436, 0.0666528940201, 0.143983960152, 0.0725592374802, -0.0377469062805, -0.0621429681778, -0.0291678905487, -0.0233603715897, -0.0589790344238, -0.0878087282181, -0.0894085168839, -0.0992587804794, -0.12716281414, -0.10996234417, -0.0140075683594, 0.0887145996094, 0.1116938591, 0.0656096935272, 0.0318957567215, 0.0276075601578, -0.00557196140289, -0.0620419979095, -0.0785014629364, -0.0634639263153, -0.0638892650604, -0.0654380321503, -0.0477347373962, -0.0402793884277, -0.0536550283432, -0.0394212007523, 0.0264414548874, 0.0816705226898, 0.0829223394394, 0.0628386735916, 0.0378696918488, 0.0166437625885, 0.0356637239456, 0.0834560394287, 0.118070602417, 0.144759297371, 0.151283144951, 0.076114654541, -0.0696769952774, -0.183663368225, -0.221519351006, -0.228063702583, -0.217722892761, -0.174036383629, -0.106649041176, -0.0122212171555, 0.118833899498, 0.236308574677, 0.269768714905, 0.234800577164, 0.190060734749, 0.144418478012, 0.0888602733612, 0.0136500597, -0.0765379667282, -0.13626730442, -0.132891178131, -0.0900590419769, -0.0593504905701, -0.04871571064, -0.0229194164276, 0.0235257148743, 0.0603049993515, 0.0668985843658, 0.0661792755127, 0.0996290445328, 0.153905391693, 0.16637468338, 0.125319004059, 0.0823652744293, 0.065669298172, 0.0669963359833, 0.0629422664642, 0.021541595459, -0.042909860611, -0.0747179985046, -0.0852746963501, -0.128432631493, -0.169097542763, -0.150745511055, -0.1074436903, -0.0884283781052, -0.0826745033264, -0.0673023462296, -0.0664476156235, -0.0873953104019, -0.0779505968094, -0.0383776426315, -0.0340982675552, -0.0751918554306, -0.110020279884, -0.109052419662, -0.0870740413666, -0.0627175569534, -0.0321307182312, 0.016660451889, 0.0757776498795, 0.120798230171, 0.144859790802, 0.165409088135, 0.188148975372, 0.186032176018, 0.141153812408, 0.0786520242691, 0.0334652662277, 0.0200488567352, 0.0282430648804, 0.0271136760712, -0.00649499893188, -0.0459004640579, -0.0203640460968, 0.0758471488953, 0.130619168282, 0.0785517692566, -0.00226128101349, -0.0453913211823, -0.072527885437, -0.105944633484, -0.143561124802, -0.168577075005, -0.152730584145, -0.102857470512, -0.0550682544708, -0.0126346349716, 0.0394934415817, 0.0883345603943, 0.116184830666, 0.127844810486, 0.130938053131, 0.126402258873, 0.12281036377, 0.122996211052, 0.10685801506, 0.071698307991, 0.0481178760529, 0.0337994098663, -0.0162537097931, -0.0977281332016, -0.142985463142, -0.134590744972, -0.128115534782, -0.135368227959, -0.116068124771, -0.0882229804993, -0.0988938808441, -0.116769552231, -0.0956203937531, -0.0792115926743, -0.126152873039, -0.20061981678, -0.231333255768, -0.224291801453, -0.22650706768, -0.237325191498, -0.23234629631, -0.208335638046, -0.170168995857, -0.113880634308, -0.0373600721359, 0.0415803194046, 0.100084066391, 0.136047959328, 0.158197402954, 0.168663144112, 0.17503464222, 0.183748602867, 0.179917097092, 0.164975643158, 0.165227890015, 0.178262233734, 0.191104412079, 0.213373303413, 0.231575727463, 0.218626976013, 0.193829655647, 0.178626894951, 0.150994181633, 0.0975459814072, 0.0396589040756, 0.0101974010468, 0.0234359502792, 0.0439151525497, 0.0345084667206, 0.0274362564087, 0.0502225160599, 0.0652347803116, 0.0650051832199, 0.0760148763657, 0.0749119520187, 0.0445163249969, 0.0244817733765, 0.0252825021744, -0.00247609615326, -0.0703966617584, -0.120843648911, -0.127715945244, -0.129064679146, -0.144930124283, -0.160046219826, -0.167795777321, -0.162889957428, -0.13577568531, -0.104312896729, -0.0975244045258, -0.111263751984, -0.132700681686, -0.160553455353, -0.171224474907, -0.14864563942, -0.120505332947, -0.110207796097, -0.115597486496, -0.119375824928, -0.0924389362335, -0.040155172348, -0.0180199146271, -0.046980381012, -0.0712546110153, -0.0496551990509, -0.0141668319702, -0.00448310375214, -0.010814666748, -0.00335240364075, 0.019683599472, 0.0463300943375, 0.077938914299, 0.109546303749, 0.119859933853, 0.100222349167, 0.0797581672668, 0.0823581218719, 0.0784336328506, 0.043930888176, 0.0121694803238, 0.0217243432999, 0.0652294158936, 0.108758568764, 0.134100794792, 0.139915585518, 0.129914879799, 0.119907259941, 0.116703152657, 0.10509455204, 0.0871064662933, 0.0742233991623, 0.0492949485779, 0.0137482881546, 0.007164478302, 0.0256586074829, 0.0265680551529, 0.0310943126678, 0.0876731872559, 0.150613903999, 0.15682220459, 0.144186496735, 0.150936126709, 0.150426268578, 0.135864257812, 0.1185734272, 0.0969045162201, 0.0889605283737, 0.104789376259, 0.116506814957, 0.12035048008, 0.142096281052, 0.164033532143, 0.154832482338, 0.135794520378, 0.136049985886, 0.148556351662, 0.152259469032, 0.134443283081, 0.113774180412, 0.126833081245, 0.158176064491, 0.155530452728, 0.123892307281, 0.107897996902, 0.110852718353, 0.105090260506, 0.0882506370544, 0.0761454105377, 0.0587908029556, 0.0346504449844, 0.0367425680161, 0.0543087720871, 0.0406510829926, 0.0134700536728, 0.015803694725, 0.0272846221924, 0.0230795145035, 0.0277423858643, 0.0429637432098, 0.0383297204971, 0.0270583629608, 0.0347118377686, 0.0385521650314, 0.0280603170395, 0.0308638811111, 0.0396318435669, 0.0280048847198, 0.0149093866348, 0.0147769451141, 0.000620245933533, -0.0199784040451, -0.00889492034912, 0.00617587566376, -0.017195224762, -0.0410323143005, -0.030522108078, -0.0156366825104, -0.00782024860382, 0.00915968418121, 0.0147882699966, -0.0151735544205, -0.0545375347137, -0.0677299499512, -0.0624564886093, -0.0660083293915, -0.0829436779022, -0.0989910364151, -0.0930023193359, -0.0633584260941, -0.0631161928177, -0.113513469696, -0.13675391674, -0.110639929771, -0.106515288353, -0.102747797966}, {-0.000192761421204, -0.00085461139679, -0.00115120410919, -0.000341415405273, 0.000319600105286, 0.000265955924988, -0.000202178955078, -0.00148606300354, -0.00210189819336, 1.81198120117e-05, 0.00361251831055, 0.00455141067505, 0.000913262367249, -0.00331735610962, -0.0034875869751, 6.55651092529e-06, 0.00358045101166, 0.00503027439117, 0.00471496582031, 0.00234794616699, -0.00269973278046, -0.00740873813629, -0.00785541534424, -0.00633823871613, -0.00457990169525, 0.00678956508636, 0.0257254838943, 0.0225070714951, -0.0104538202286, -0.0327391624451, -0.0231121778488, -0.00215125083923, 0.0193510055542, 0.0293642282486, 0.00822710990906, -0.0152727365494, -0.00352394580841, 0.0119558572769, -0.00755429267883, -0.0278813838959, -0.00713777542114, 0.0153838396072, -0.00209593772888, -0.00503194332123, 0.0357797145844, 0.0404226779938, -0.0108729600906, -0.0333052873611, -0.0105992555618, 0.00551676750183, 0.016508936882, 0.0259532928467, -0.00383937358856, -0.0372663736343, 0.00660717487335, 0.07679438591, 0.0505822896957, -0.049036026001, -0.0802829265594, -0.00583827495575, 0.0601456165314, 0.0363385677338, -0.0230997800827, -0.0310806035995, 0.0112973451614, 0.0317829847336, 0.0101273059845, -0.00253295898438, 0.000715732574463, -0.009153008461, -0.00494277477264, 0.0256403684616, 0.0214313268661, -0.0212072134018, -0.0236721038818, 0.0146077871323, 0.0199196338654, -0.00773596763611, -0.0119495391846, 0.011954665184, 0.0186536312103, -0.0134279727936, -0.0347137451172, 0.00506150722504, 0.0502969026566, 0.0233587026596, -0.0350902080536, -0.0343332290649, 0.0231071710587, 0.0459909439087, -0.0106537342072, -0.0658123493195, -0.0275503396988, 0.0562317371368, 0.0610976219177, -0.0155833959579, -0.0366934537888, 0.0357282161713, 0.0491367578506, -0.0379854440689, -0.0486721992493, 0.0388542413712, 0.0546382665634, 0.0103240013123, 0.00984954833984, 0.0111840963364, -0.00497269630432, -0.00426054000854, -0.010307431221, -0.00270295143127, 0.0223675966263, -0.0239375829697, -0.0860751867294, -0.0156461000443, 0.094153881073, 0.0609335899353, -0.0458705425262, -0.0649310350418, -0.0202709436417, -0.00892174243927, -0.0196404457092, -0.00889873504639, -0.00266182422638, -0.0260392427444, -0.035795211792, 0.00155127048492, 0.0399794578552, 0.0314071178436, -0.0074211359024, -0.0477871894836, -0.0697356462479, -0.0393723249435, 0.0306401252747, 0.0492023229599, -0.014964222908, -0.0600744485855, -0.0248036384583, 0.0299702882767, 0.0601418018341, 0.0719324350357, 0.0477390289307, -0.0312345027924, -0.115864753723, -0.124678611755, -0.0582727193832, 0.00781381130219, 0.0340223312378, 0.0449186563492, 0.0597946643829, 0.0318584442139, -0.062571644783, -0.127737760544, -0.0996601581573, -0.0412319898605, 0.0112015008926, 0.0669889450073, 0.0877066850662, 0.0537478923798, 0.00753104686737, -0.0130257606506, -0.00836682319641, -0.00813341140747, -0.0123323202133, 0.00883197784424, 0.0117037296295, -0.0470473766327, -0.0630693435669, 0.0373340845108, 0.121937513351, 0.0845279693604, 0.015447974205, 0.00882291793823, 0.0277416706085, 0.00428068637848, -0.0582939386368, -0.0962828397751, -0.0828891992569, -0.086167216301, -0.144235134125, -0.165635228157, -0.0805734395981, 0.0428359508514, 0.0995942354202, 0.0843011140823, 0.0857862234116, 0.104489803314, 0.0440244674683, -0.0595426559448, -0.0847828388214, -0.0570493936539, -0.067809343338, -0.0881155729294, -0.0603454113007, -0.0207514762878, -0.0180268287659, -0.030344247818, -0.00881850719452, 0.0421105623245, 0.0797582864761, 0.0764435529709, 0.0372532606125, 0.017053604126, 0.0337249040604, 0.0418490171432, 0.0744965076447, 0.164848804474, 0.208626866341, 0.144261956215, 0.0396437644958, -0.0605382919312, -0.156127214432, -0.228829026222, -0.252714514732, -0.235967159271, -0.203270792961, -0.132311940193, 0.00919651985168, 0.175945878029, 0.268840193748, 0.268380522728, 0.240674734116, 0.211361408234, 0.167909622192, 0.0866068601608, -0.0351513624191, -0.123690366745, -0.131555914879, -0.104892253876, -0.0896093845367, -0.0759173631668, -0.0449488162994, 0.00062620639801, 0.0454300642014, 0.0581026077271, 0.0475729703903, 0.0759763717651, 0.139454007149, 0.161625146866, 0.133117794991, 0.113324761391, 0.112917304039, 0.106191396713, 0.0859014987946, 0.0420674085617, -0.0155715942383, -0.0441207885742, -0.0570759773254, -0.111344456673, -0.16953599453, -0.161910533905, -0.125408768654, -0.120119333267, -0.126525878906, -0.10605597496, -0.0877331495285, -0.0990223884583, -0.0805603265762, -0.0159198045731, 0.00399518013, -0.0519312620163, -0.105885028839, -0.112189054489, -0.103074669838, -0.09958589077, -0.0781506299973, -0.0265816450119, 0.03003013134, 0.074729681015, 0.117961406708, 0.160211920738, 0.187848925591, 0.190122008324, 0.165030002594, 0.123521924019, 0.0796780586243, 0.0548543930054, 0.0614901781082, 0.064723610878, 0.021869301796, -0.0362877845764, -0.0190279483795, 0.0791826248169, 0.126987099648, 0.0597159862518, -0.0249691009521, -0.0601810216904, -0.0839623212814, -0.118795990944, -0.150843501091, -0.167885184288, -0.150171279907, -0.101722121239, -0.0556447505951, -0.0112019777298, 0.0434726476669, 0.0857917070389, 0.105872273445, 0.119305968285, 0.12347972393, 0.111015081406, 0.103291511536, 0.113363265991, 0.111376285553, 0.0791529417038, 0.0513436794281, 0.0489847660065, 0.0226852893829, -0.0579797029495, -0.123690366745, -0.127236604691, -0.126717090607, -0.14435005188, -0.129541397095, -0.0976991653442, -0.101307272911, -0.111405491829, -0.0840729475021, -0.0628107786179, -0.109807610512, -0.191138625145, -0.229722619057, -0.230021834373, -0.234694242477, -0.244272589684, -0.247979521751, -0.235166788101, -0.20995414257, -0.178864240646, -0.114211440086, -0.0255954265594, 0.0523022413254, 0.11520254612, 0.152947425842, 0.175349473953, 0.200063586235, 0.210049510002, 0.193269252777, 0.174283504486, 0.179948091507, 0.185304999352, 0.179605841637, 0.197124123573, 0.21948826313, 0.210253477097, 0.191252827644, 0.185084700584, 0.16947042942, 0.125492215157, 0.0710488557816, 0.0402958393097, 0.0524355173111, 0.071936249733, 0.0568405389786, 0.0392682552338, 0.0501716136932, 0.0573630332947, 0.0495140552521, 0.0494906902313, 0.045107126236, 0.0261204242706, 0.02414894104, 0.0375249385834, 0.014106631279, -0.0534394979477, -0.102800130844, -0.105291247368, -0.109929203987, -0.144696831703, -0.177840709686, -0.190402984619, -0.18549311161, -0.157895803452, -0.122732162476, -0.114223837852, -0.126601219177, -0.134878158569, -0.152051210403, -0.177843213081, -0.176878929138, -0.151265501976, -0.135473132133, -0.143785595894, -0.15488409996, -0.129732012749, -0.0766911506653, -0.0549751520157, -0.0800240039825, -0.0987499952316, -0.0773886442184, -0.0435916185379, -0.0291985273361, -0.0285896062851, -0.0203902721405, 0.000233054161072, 0.029460310936, 0.0700037479401, 0.109364151955, 0.117712259293, 0.0906760692596, 0.0715745687485, 0.087619304657, 0.0960998535156, 0.0613621473312, 0.0170302391052, 0.0109630823135, 0.0460950136185, 0.0911339521408, 0.124280691147, 0.134179830551, 0.11591219902, 0.0977945327759, 0.105137586594, 0.11076259613, 0.0938899517059, 0.0784620046616, 0.0640172958374, 0.0298987627029, 0.00499713420868, 0.0137763023376, 0.0201592445374, 0.0219570398331, 0.0671867132187, 0.125354290009, 0.135547161102, 0.135387659073, 0.152139186859, 0.139340758324, 0.107792854309, 0.101982951164, 0.0984174013138, 0.0752111673355, 0.0697671175003, 0.105651974678, 0.145751237869, 0.152546286583, 0.148759961128, 0.162485361099, 0.164720654488, 0.143049836159, 0.145097017288, 0.171081423759, 0.156491041183, 0.106690406799, 0.10265815258, 0.150457024574, 0.168207764626, 0.138384103775, 0.121717572212, 0.128756761551, 0.117630720139, 0.0872167348862, 0.0733103752136, 0.0701878070831, 0.0435500144958, 0.0127822160721, 0.0187215805054, 0.0410505533218, 0.0393152236938, 0.0268952846527, 0.0301657915115, 0.0369806289673, 0.0378012657166, 0.0396713018417, 0.0387569665909, 0.0333454608917, 0.0255023241043, 0.0123689174652, 0.00786972045898, 0.0259284973145, 0.0408878326416, 0.0300801992416, 0.0199385881424, 0.0333837270737, 0.0383894443512, 0.00269329547882, -0.0267180204391, -0.00387227535248, 0.00723683834076, -0.0380184650421, -0.0673854351044, -0.0426073074341, -0.0131794214249, -0.00309932231903, 0.00281810760498, -0.00200748443604, -0.0378472805023, -0.0866978168488, -0.102697730064, -0.0819500684738, -0.0676990747452, -0.0881232023239, -0.115472435951, -0.0921368598938, -0.0434666872025, -0.0753971338272, -0.159474134445, -0.156057715416, -0.0912288427353, -0.0787782669067, -0.0878517627716}};

} // end namespace