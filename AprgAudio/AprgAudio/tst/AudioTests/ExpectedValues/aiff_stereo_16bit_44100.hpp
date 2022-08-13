#include <vector>

namespace aiff_stereo_16bit_44100 {

int numSamplesPerChannel = 352800;
int bitDepth = 16;
int sampleRate = 44100;
int numChannels = 2;

std::vector<std::vector<double>> testBuffer = {
    {-0.00942993164062, -0.0304260253906,  -0.0351867675781,  0.170715332031,    -0.0195922851562,  -0.115539550781,     0.0654907226562,   0.0146179199219,   -0.0125122070312,  -0.038818359375,   -0.0511169433594,  0.0557556152344,
     0.0522155761719,   0.0104064941406,   -0.0538330078125,  -0.0388488769531,  0.0592956542969,   -0.00265502929688,
     -0.00460815429688, 0.0627746582031,   0.0336303710938,   0.0408630371094,   -0.00921630859375, -0.0555725097656,
     -0.0155334472656,  -0.0706481933594,  -0.0711669921875,  0.0555419921875,   0.142486572266,    0.0445861816406,
     -0.140930175781,   -0.04248046875,    0.116851806641,    0.0307006835938,   -0.0695495605469,  -0.035400390625,
     0.121215820312,    0.0785522460938,   -0.138793945312,   0.037109375,       0.182250976562,    -0.128540039062,
     -0.0716857910156,  0.222229003906,    -0.0207824707031,  -0.175018310547,   0.0807189941406,   0.116790771484,
     -0.0332336425781,  -0.00732421875,    0.0682067871094,   -0.014404296875,   -0.0166320800781,  0.128784179688,
     0.0617065429688,   -0.0335998535156,  0.129180908203,    0.152374267578,    -0.0736083984375,  -0.0822143554688,
     0.121520996094,    0.100158691406,    -0.0691223144531,  0.015380859375,    0.158447265625,    0.0256042480469,
     -0.0297546386719,  0.131225585938,    0.0602111816406,   -0.105621337891,   0.0500793457031,   0.215393066406,
     0.0495910644531,   -0.0668029785156,  0.0919189453125,   0.0134582519531,   -0.132843017578,   0.152252197266,
     0.186706542969,    -0.0793151855469,  0.0259094238281,   0.135131835938,    -0.00177001953125, -0.0415649414062,
     0.0414123535156,   -0.0232543945312,  -0.108215332031,   0.0657043457031,   0.0894165039062,   -0.0679016113281,
     -0.0374145507812,  0.0125122070312,   0.0804748535156,   0.0330200195312,   -0.148468017578,   -0.0191345214844,
     0.0653381347656,   -0.136505126953,   -0.0656127929688,  0.0942993164062,   -0.0206604003906,  -0.0557861328125,
     -0.0456237792969,  -0.090576171875,   -0.0609436035156,  -0.0792236328125,  -0.0170288085938,  -0.00271606445312,
     -0.141143798828,   -0.109558105469,   -0.0343322753906,  -0.0232849121094,  -0.0355529785156,  -0.108337402344,
     -0.103363037109,   -0.0357055664062,  -0.0582275390625,  -0.142639160156,   -0.167572021484,   -0.0793151855469,
     -0.044677734375,   -0.146118164062,   -0.144409179688,   -0.0755310058594,  -0.0811462402344,  -0.104156494141,
     -0.126373291016,   -0.119445800781,   -0.158905029297,   -0.167388916016,   -0.100952148438,   -0.134307861328,
     -0.156555175781,   -0.0981140136719,  -0.110473632812,   -0.15087890625,    -0.125732421875,   -0.140380859375,
     -0.166748046875,   -0.0766906738281,  -0.0444030761719,  -0.152130126953,   -0.176147460938,   -0.0623779296875,
     -0.00900268554688, -0.0835266113281,  -0.1474609375,     -0.133361816406,   -0.0874328613281,  -0.0911254882812,
     -0.159545898438,   -0.113830566406,   0.0025634765625,   -0.108612060547,   -0.176055908203,   -0.0173645019531,
     -0.0562133789062,  -0.171630859375,   -0.0487365722656,  0.0777893066406,   -0.0188598632812,  -0.144775390625,
     -0.0627136230469,  -0.01025390625,    -0.0758361816406,  -0.0578308105469,  -0.00714111328125, 0.0163879394531,
     -0.0173645019531,  -0.0154113769531,  0.061767578125,    0.0112609863281,   -0.0439453125,     0.0266418457031,
     0.056884765625,    0.0227661132812,   0.0557861328125,   0.0974731445312,   0.0220642089844,   -0.0238342285156,
     0.0378723144531,   0.139526367188,    0.0946044921875,   -0.0333557128906,  0.108337402344,    0.190093994141,
     0.0584716796875,   0.0591735839844,   0.0888061523438,   0.0999755859375,   0.104644775391,    0.0665588378906,
     0.0899963378906,   0.126220703125,    0.135803222656,    0.150634765625,    0.122833251953,    0.0722351074219,
     0.103942871094,    0.136077880859,    0.124969482422,    0.144622802734,    0.116241455078,    0.114501953125,
     0.176147460938,    0.139617919922,    0.0980529785156,   0.158355712891,    0.149963378906,    0.0531921386719,
     0.0902404785156,   0.182586669922,    0.175506591797,    0.164733886719,    0.122100830078,    0.103729248047,
     0.137329101562,    0.112823486328,    0.122253417969,    0.138885498047,    0.150299072266,    0.150085449219,
     0.0964050292969,   0.0909118652344,   0.0183715820312,   -0.038330078125,   0.0259094238281,   0.00143432617188,
     -0.0140991210938,  0.0623779296875,   0.112518310547,    0.163452148438,    0.246643066406,    0.253265380859,
     0.236114501953,    0.298248291016,    0.243194580078,    0.172027587891,    0.246154785156,    0.216766357422,
     0.134552001953,    0.121490478516,    0.114196777344,    0.08935546875,     -0.00723266601562, -0.0238037109375,
     0.0134582519531,   -0.071044921875,   -0.0921020507812,  -0.0514831542969,  -0.0833129882812,  -0.127166748047,
     -0.137054443359,   -0.0772399902344,  -0.0535583496094,  -0.0884399414062,  -0.0982360839844,  -0.14013671875,
     -0.120544433594,   -0.0447692871094,  -0.11083984375,    -0.152679443359,   -0.0603637695312,  -0.0603332519531,
     -0.1005859375,     -0.0758666992188,  -0.0215454101562,  0.022705078125,    -0.0204467773438,  0.00494384765625,
     0.0691833496094,   0.0797424316406,   0.158416748047,    0.142669677734,    0.0808410644531,   0.112182617188,
     0.0828857421875,   0.0223388671875,   0.0189514160156,   0.0566101074219,   0.0603942871094,   0.02294921875,
     0.000701904296875, -0.0201721191406,  0.01123046875,     0.031005859375,    -0.0388488769531,  -0.0326538085938,
     0.0124206542969,   -0.0505676269531,  -0.0995178222656,  -0.0781860351562,  -0.101196289062,   -0.133178710938,
     -0.130584716797,   -0.162414550781,   -0.175506591797,   -0.164947509766,   -0.161773681641,   -0.119079589844,
     -0.118713378906,   -0.174957275391,   -0.165893554688,   -0.157562255859,   -0.223480224609,   -0.228820800781,
     -0.17333984375,    -0.190582275391,   -0.242858886719,   -0.215728759766,   -0.159027099609,   -0.172882080078,
     -0.198516845703,   -0.179077148438,   -0.162689208984,   -0.188690185547,   -0.211730957031,   -0.203979492188,
     -0.207122802734,   -0.184112548828,   -0.162811279297,   -0.190246582031,   -0.1748046875,     -0.14013671875,
     -0.142974853516,   -0.149322509766,   -0.123657226562,   -0.0967102050781,  -0.12646484375,    -0.130645751953,
     -0.0777893066406,  -0.0425415039062,  -0.0600280761719,  -0.0491638183594,  0.0431518554688,   0.0528564453125,
     0.01708984375,     0.0694274902344,   0.1015625,         0.104797363281,    0.111206054688,    0.106781005859,
     0.168792724609,    0.215240478516,    0.164184570312,    0.156829833984,    0.200408935547,    0.196014404297,
     0.158477783203,    0.147491455078,    0.172485351562,    0.176086425781,    0.156982421875,    0.145202636719,
     0.141540527344,    0.143707275391,    0.128875732422,    0.0832824707031,   0.0904541015625,   0.121429443359,
     0.0603332519531,   0.0686340332031,   0.142333984375,    0.122314453125,    0.137268066406,    0.163848876953,
     0.150085449219,    0.189056396484,    0.202056884766,    0.193969726562,    0.219818115234,    0.232360839844,
     0.224822998047,    0.198516845703,    0.188720703125,    0.179992675781,    0.14501953125,     0.146270751953,
     0.163391113281,    0.173645019531,    0.180633544922,    0.133514404297,    0.111175537109,    0.134399414062,
     0.0823669433594,   0.0227355957031,   0.0251159667969,   0.0136413574219,   -0.0158081054688,  -0.0114440917969,
     0.0246887207031,   0.019287109375,    -0.0201110839844,  0.0008544921875,   0.00808715820312,  -0.0192260742188,
     -0.00466918945312, -0.00848388671875, -0.0129089355469,  -0.00213623046875, -0.00225830078125, 0.0054931640625,
     -0.00149536132812, 0.0122985839844,   0.0263977050781,   0.0116577148438,   0.00335693359375,  -0.00210571289062,
     0.0208435058594,   0.0227661132812,   -0.0299682617188,  -0.0273132324219,  -0.0285034179688,  -0.0985717773438,
     -0.0845336914062,  -0.0437927246094,  -0.0887451171875,  -0.09521484375,    -0.0765075683594,  -0.087890625,
     -0.0940856933594,  -0.102294921875,   -0.0846557617188,  -0.0712585449219,  -0.104370117188,   -0.0978698730469,
     -0.0634460449219,  -0.0632019042969,  -0.0355834960938,  0.00149536132812,  0.00363159179688,  -0.000579833984375,
     -0.00479125976562, 0.000457763671875, -0.00103759765625, -0.0437927246094,  -0.0798645019531,  -0.0844116210938,
     -0.106689453125,   -0.130645751953,   -0.136871337891,   -0.120819091797,   -0.103942871094,   -0.125061035156,
     -0.101989746094,   -0.0474243164062,  -0.0385131835938,  -0.018798828125,   6.103515625e-05,   -0.0032958984375,
     0.0238952636719,   0.0472717285156,   0.0184631347656,   -0.0032958984375,  0.0227355957031,   0.0242004394531,
     -0.00927734375,    -0.014892578125,   -0.0248107910156,  -0.0449829101562,  -0.0562744140625,  -0.0721130371094,
     -0.0736389160156,  -0.06494140625,    -0.0654602050781,  -0.0618896484375,  -0.0347290039062,  -0.0125427246094,
     -0.0146484375,     -0.0078125,        -0.0121459960938,  -0.0214538574219,  -0.010986328125,   -0.0117492675781,
     -0.0126953125,     -0.0233154296875,  -0.0403747558594,  -0.0252380371094,  -0.00283813476562, -0.00772094726562,
     -0.0226745605469,  -0.0156860351562,  -0.0124816894531,  -0.0132751464844,  -0.0062255859375,  -0.022705078125,
     -0.0268859863281,  -0.0237121582031,  -0.0519714355469,  -0.048828125,      -0.0289306640625,  -0.0340576171875,
     -0.0219116210938,  0.00393676757812,  0.0279235839844,   0.0218811035156,   -0.00665283203125, 0.0166931152344,
     0.0527648925781,   0.0342712402344},

    {-0.00778198242188, -0.0250854492188,  -0.029052734375,   0.140869140625,    -0.01611328125,    -0.095458984375,
     0.0540161132812,   0.0119323730469,   -0.0102233886719,  -0.0318908691406,  -0.0419921875,     0.0461120605469,
     0.0430297851562,   0.00836181640625,  -0.0445251464844,  -0.0322875976562,  0.0487365722656,   -0.00241088867188,
     -0.00411987304688, 0.0516662597656,   0.0269775390625,   0.0339965820312,   -0.00833129882812, -0.0472717285156,
     -0.0116271972656,  -0.0613403320312,  -0.0636901855469,  0.0505676269531,   0.115875244141,    0.0258178710938,
     -0.114562988281,   -0.0263061523438,  0.0960998535156,   0.013671875,       -0.0719299316406,  -0.0297241210938,
     0.117401123047,    0.0748596191406,   -0.143341064453,   -0.00653076171875, 0.169342041016,    -0.0707092285156,
     -0.0862426757812,  0.136779785156,    -0.0105285644531,  -0.126770019531,   0.0474243164062,   0.0853881835938,
     -0.0152282714844,  0.00241088867188,  0.0445556640625,   -0.0525817871094,  -0.034423828125,   0.124145507812,
     0.0509643554688,   -0.0764770507812,  0.0342407226562,   0.094482421875,    -0.0336608886719,  -0.0494079589844,
     0.0785827636719,   0.0553588867188,   -0.0574951171875,  0.0203552246094,   0.100433349609,    -0.0221557617188,
     -0.0322875976562,  0.108459472656,    0.0307006835938,   -0.09619140625,    0.0293273925781,   0.131469726562,
     0.0103759765625,   -0.052734375,      0.0662841796875,   -0.00958251953125, -0.125244140625,   0.113067626953,
     0.150970458984,    -0.0653991699219,  0.0111389160156,   0.0939636230469,   -0.0181579589844,  -0.0455017089844,
     0.0360412597656,   -0.0130615234375,  -0.0964660644531,  0.0436096191406,   0.073486328125,    -0.0570373535156,
     -0.0423889160156,  0.00350952148438,  0.0645751953125,   0.0259399414062,   -0.108215332031,   0.001708984375,
     0.0664367675781,   -0.0893859863281,  -0.026611328125,   0.0919494628906,   -0.0174865722656,  -0.0565795898438,
     -0.0305480957031,  -0.0310363769531,  -0.0108642578125,  -0.0548095703125,  -0.00814819335938, 0.0190124511719,
     -0.0768432617188,  -0.0560913085938,  -0.020751953125,   -0.0145874023438,  0.00576782226562,  -0.0301818847656,
     -0.0570373535156,  -0.0317077636719,  -0.00396728515625, -0.0480346679688,  -0.108459472656,   -0.0464477539062,
     0.0162048339844,   -0.0521240234375,  -0.0800476074219,  -0.0433959960938,  -0.0306396484375,  -0.0360107421875,
     -0.0577392578125,  -0.0587768554688,  -0.0797119140625,  -0.0787353515625,  -0.0491943359375,  -0.0889282226562,
     -0.0828552246094,  -0.0192260742188,  -0.0555114746094,  -0.105194091797,   -0.0508422851562,  -0.041015625,
     -0.0833740234375,  -0.0317687988281,  -3.0517578125e-05, -0.0700988769531,  -0.101135253906,   -0.0319519042969,
     0.022705078125,    -0.0101013183594,  -0.0698547363281,  -0.106628417969,   -0.0692443847656,  -0.0113525390625,
     -0.0545654296875,  -0.0625305175781,  9.1552734375e-05,  -0.06982421875,    -0.106781005859,   -0.00369262695312,
     -0.0302429199219,  -0.0944213867188,  -0.0192260742188,  0.0498657226562,   -0.0126953125,     -0.0922546386719,
     -0.043212890625,   -0.018310546875,   -0.0484619140625,  -0.00534057617188, 0.0389404296875,   0.0348205566406,
     -0.0123901367188,  -0.0114440917969,  0.0300598144531,   -0.0152282714844,  -0.02685546875,    0.0303955078125,
     0.0353088378906,   -9.1552734375e-05, 0.0278930664062,   0.0704956054688,   0.00344848632812,  -0.0446472167969,
     0.00933837890625,  0.0955200195312,   0.0654602050781,   -0.0450439453125,  0.0574035644531,   0.135314941406,
     0.0241394042969,   0.014404296875,    0.0509338378906,   0.0550842285156,   0.0499572753906,   0.0243835449219,
     0.0334777832031,   0.0514831542969,   0.0680541992188,   0.0950317382812,   0.0691833496094,   0.0150146484375,
     0.0382995605469,   0.0594787597656,   0.0408020019531,   0.0637512207031,   0.052001953125,    0.0469970703125,
     0.0912780761719,   0.0679626464844,   0.0466613769531,   0.0988159179688,   0.0744934082031,   -0.0135192871094,
     0.033447265625,    0.101318359375,    0.076904296875,    0.0647277832031,   0.0325927734375,   0.0303344726562,
     0.0588073730469,   0.0361022949219,   0.0556335449219,   0.0752563476562,   0.0865783691406,   0.0860900878906,
     0.0304870605469,   0.00180053710938,  -0.0709838867188,  -0.0982055664062,  -0.0289916992188,  -0.0535583496094,
     -0.0777893066406,  -0.0180969238281,  0.0467834472656,   0.120819091797,    0.196899414062,    0.192718505859,
     0.170928955078,    0.228240966797,    0.202850341797,    0.143218994141,    0.1767578125,      0.150665283203,
     0.103668212891,    0.10107421875,     0.077880859375,    0.0350952148438,   -0.0391235351562,  -0.04345703125,
     -0.0218811035156,  -0.0905151367188,  -0.102416992188,   -0.0773315429688,  -0.100158691406,   -0.126373291016,
     -0.141784667969,   -0.104064941406,   -0.07568359375,    -0.0809631347656,  -0.0760803222656,  -0.126373291016,
     -0.124786376953,   -0.0420227050781,  -0.0787658691406,  -0.126281738281,   -0.0654296875,     -0.0625915527344,
     -0.0731201171875,  -0.0334167480469,  -0.00018310546875, 0.0277709960938,   0.0165710449219,   0.060546875,
     0.111297607422,    0.112274169922,    0.176422119141,    0.176513671875,    0.13916015625,     0.160980224609,
     0.129608154297,    0.0814208984375,   0.0892333984375,   0.114410400391,    0.100219726562,    0.0780639648438,
     0.0691528320312,   0.0376586914062,   0.05810546875,     0.0807800292969,   0.0199584960938,   0.0305480957031,
     0.0833129882812,   0.03369140625,     -0.0180969238281,  -0.00894165039062, -0.0244445800781,  -0.0590515136719,
     -0.0745544433594,  -0.102600097656,   -0.114868164062,   -0.0939025878906,  -0.0749206542969,  -0.0550537109375,
     -0.0742797851562,  -0.113586425781,   -0.0874938964844,  -0.0816955566406,  -0.148345947266,   -0.160308837891,
     -0.120300292969,   -0.132568359375,   -0.172576904297,   -0.151306152344,   -0.100616455078,   -0.111022949219,
     -0.128936767578,   -0.117645263672,   -0.117340087891,   -0.144439697266,   -0.171203613281,   -0.152923583984,
     -0.140686035156,   -0.141448974609,   -0.128723144531,   -0.139892578125,   -0.135467529297,   -0.108489990234,
     -0.113708496094,   -0.132019042969,   -0.106842041016,   -0.0736083984375,  -0.0901794433594,  -0.0857849121094,
     -0.0520629882812,  -0.0450134277344,  -0.0595703125,     -0.0331115722656,  0.0509643554688,   0.0627746582031,
     0.0284118652344,   0.0628967285156,   0.08935546875,     0.0962219238281,   0.111419677734,    0.107971191406,
     0.145233154297,    0.184722900391,    0.146026611328,    0.132080078125,    0.174285888672,    0.173431396484,
     0.130035400391,    0.120269775391,    0.139892578125,    0.139221191406,    0.129577636719,    0.109100341797,
     0.0856628417969,   0.093994140625,    0.0835266113281,   0.0277099609375,   0.0283508300781,   0.0575561523438,
     0.0150451660156,   0.0226440429688,   0.071044921875,    0.0557861328125,   0.0765075683594,   0.100250244141,
     0.0892028808594,   0.122009277344,    0.132537841797,    0.117462158203,    0.143524169922,    0.168243408203,
     0.15576171875,     0.125396728516,    0.115295410156,    0.103790283203,    0.0726623535156,   0.0721435546875,
     0.0859985351562,   0.100708007812,    0.110046386719,    0.0616455078125,   0.03515625,        0.0511779785156,
     0.00167846679688,  -0.0459594726562,  -0.0464782714844,  -0.0700073242188,  -0.0931091308594,  -0.0693054199219,
     -0.0293579101562,  -0.0476989746094,  -0.0967712402344,  -0.0730285644531,  -0.0552062988281,  -0.0810852050781,
     -0.0688781738281,  -0.0635375976562,  -0.067138671875,   -0.0538940429688,  -0.0509948730469,  -0.0600280761719,
     -0.0668334960938,  -0.0323486328125,  -0.00848388671875, -0.0293579101562,  -0.0455017089844,  -0.0461120605469,
     -0.0171508789062,  -0.00759887695312, -0.0571594238281,  -0.0631713867188,  -0.057373046875,   -0.108520507812,
     -0.0994873046875,  -0.0782470703125,  -0.119537353516,   -0.111358642578,   -0.0833435058594,  -0.0900268554688,
     -0.0958251953125,  -0.100677490234,   -0.0806579589844,  -0.0738525390625,  -0.103668212891,   -0.0878601074219,
     -0.0567016601562,  -0.0525817871094,  -0.0136108398438,  0.0298461914062,   0.0267639160156,   0.0165405273438,
     0.02197265625,     0.0348205566406,   0.0289611816406,   -0.0116882324219,  -0.0407409667969,  -0.0475158691406,
     -0.0700073242188,  -0.0882263183594,  -0.089599609375,   -0.0730895996094,  -0.0630493164062,  -0.0747985839844,
     -0.0425415039062,  0.00515747070312,  0.0180969238281,   0.0409240722656,   0.0583801269531,   0.0565795898438,
     0.07958984375,     0.106414794922,    0.0928955078125,   0.0724792480469,   0.0799560546875,   0.0760192871094,
     0.055908203125,    0.0606689453125,   0.0534973144531,   0.0237121582031,   0.00521850585938,  -0.0037841796875,
     0.00430297851562,  0.0115356445312,   -0.0072021484375,  -0.00933837890625, 0.0350952148438,   0.0711975097656,
     0.0639953613281,   0.0566101074219,   0.0515747070312,   0.0482482910156,   0.0564880371094,   0.0536804199219,
     0.0452270507812,   0.0355529785156,   0.0276794433594,   0.0384521484375,   0.0545654296875,   0.0496215820312,
     0.0317687988281,   0.0352172851562,   0.0406188964844,   0.0380859375,      0.0395202636719,   0.0201110839844,
     0.0157165527344,   0.0211791992188,   -0.0100402832031,  -0.0150451660156,  0.00650024414062,  0.00369262695312,
     0.00827026367188,  0.0278015136719,   0.0538024902344,   0.0499572753906,   0.017578125,       0.0290222167969,
     0.0606079101562,   0.0499572753906}};

}  // namespace aiff_stereo_16bit_44100
