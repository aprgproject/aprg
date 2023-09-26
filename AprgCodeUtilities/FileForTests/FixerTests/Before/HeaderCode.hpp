namespace{
	constexpr int CONST_NUMBER1=1;
	constexpr int CONST_NUMBER2=2;
	constexpr int CONST_NUMBER3=3;
	constexpr int constFunction(int const number){
	    constexpr int CONST_NUMBER_INSIDE_FUNCTION=1;
		return number;
	}
}

namespace itHasAName{
	constexpr int CONST_NUMBER1=1;
	constexpr int CONST_NUMBER2=2;
	constexpr int CONST_NUMBER3=3;
	constexpr int constFunction(int const number){
	    constexpr int CONST_NUMBER_INSIDE_FUNCTION=1;
		return number;
	}
}