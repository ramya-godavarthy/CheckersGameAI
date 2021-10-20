
#ifndef Algorithm_h
#define Algorithm_h

//****** Functions for the Algorithms ******//

extern vector<Element> bestPath;

// Minmax AB Declaration
Element MinMaxAB(Element& e, int depth, char player, int useThresh, int passThresh);

//Alpha Beta Search Declaration.
void alpha_beta_search(Element state, char[][8]);

//Alpha Beta Search Max Function Declaration
int max_value(Element& state, int alpha, int beta);

//Alpha Beta Search Min Function Declaration
int min_value(Element& state, int alpha, int beta);

extern int depth;
#endif /* Algorithm_h */
