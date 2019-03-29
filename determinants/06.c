int libinfo_N = 13;
int libinfo_K = 48;

int determinantQ(int *x)
{
    return x[3]*(-(x[5]*(x[7]*x[8]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9]) + x[6]*(x[8]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9]) + x[7]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9] + x[8]*(x[10]*x[11]*(6 - 5*x[12]) + (x[11]*(6 - 5*x[12]) + x[10]*(6 + 4*x[11]*(-2 + x[12]) - 5*x[12]))*x[9]))))) + x[4]*(x[7]*x[8]*(-6*x[10]*x[11]*x[12] + (-6*x[11]*x[12] + x[10]*(-6*x[12] + x[11]*(-6 + 5*x[12])))*x[9]) - x[6]*(x[8]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9]) + x[7]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9] + x[8]*(x[10]*x[11]*(6 - 5*x[12]) + (x[11]*(6 - 5*x[12]) + x[10]*(6 + 4*x[11]*(-2 + x[12]) - 5*x[12]))*x[9]))) + x[5]*(x[7]*x[8]*((-6*x[11] + x[10]*(-6 + 5*x[11]))*x[12] + (2*x[11]*(-3 + 4*x[12]) + x[10]*(-6 + x[11]*(5 - 4*x[12]) + 8*x[12]))*x[9]) + x[6]*(x[8]*((-6*x[11] + x[10]*(-6 + 5*x[11]))*x[12] + (2*x[11]*(-3 + 4*x[12]) + x[10]*(-6 + x[11]*(5 - 4*x[12]) + 8*x[12]))*x[9]) + x[7]*((-6*x[11] + x[10]*(-6 + 5*x[11]))*x[12] + (2*x[11]*(-3 + 4*x[12]) + x[10]*(-6 + x[11]*(5 - 4*x[12]) + 8*x[12]))*x[9] + x[8]*(x[11]*(-6 + 5*x[12] + (9 - 6*x[12])*x[9]) + x[10]*(-6 + x[11]*(5 - 4*x[12]) + 5*x[12] + 3*(3 + x[11]*(-2 + x[12]) - 2*x[12])*x[9]))))))) - x[2]*(x[5]*(x[7]*x[8]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9]) + x[6]*(x[8]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9]) + x[7]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9] + x[8]*(x[10]*x[11]*(6 - 5*x[12]) + (x[11]*(6 - 5*x[12]) + x[10]*(6 + 4*x[11]*(-2 + x[12]) - 5*x[12]))*x[9])))) + x[4]*(x[7]*x[8]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9]) + x[6]*(x[8]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9]) + x[7]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9] + x[8]*(x[10]*x[11]*(6 - 5*x[12]) + (x[11]*(6 - 5*x[12]) + x[10]*(6 + 4*x[11]*(-2 + x[12]) - 5*x[12]))*x[9]))) + x[5]*(x[7]*x[8]*((x[10]*(6 - 5*x[11]) + 6*x[11])*x[12] + (2*x[11]*(3 - 4*x[12]) + x[10]*(6 - 8*x[12] + x[11]*(-5 + 4*x[12])))*x[9]) + x[6]*(x[8]*((x[10]*(6 - 5*x[11]) + 6*x[11])*x[12] + (2*x[11]*(3 - 4*x[12]) + x[10]*(6 - 8*x[12] + x[11]*(-5 + 4*x[12])))*x[9]) + x[7]*((x[10]*(6 - 5*x[11]) + 6*x[11])*x[12] + (2*x[11]*(3 - 4*x[12]) + x[10]*(6 - 8*x[12] + x[11]*(-5 + 4*x[12])))*x[9] + x[8]*(x[11]*(6 - 5*x[12] + (-9 + 6*x[12])*x[9]) + x[10]*(6 - 5*x[12] + x[11]*(-5 + 4*x[12]) + (-9 - 3*x[11]*(-2 + x[12]) + 6*x[12])*x[9])))))) + x[3]*(x[5]*(x[7]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9] + x[8]*(x[11]*x[12]*(6 - 5*x[9]) + x[10]*(x[12]*(6 - 5*x[9]) + x[11]*(6 - 8*x[12] + (-5 + 4*x[12])*x[9])))) + x[6]*(6*x[10]*x[11]*x[12] + 6*x[10]*x[11]*x[9] + 6*x[10]*x[12]*x[9] + 6*x[11]*x[12]*x[9] - 5*x[10]*x[11]*x[12]*x[9] + x[8]*(x[11]*x[12]*(6 - 5*x[9]) + x[10]*(x[12]*(6 - 5*x[9]) + x[11]*(6 - 8*x[12] + (-5 + 4*x[12])*x[9]))) + x[7]*(3*(x[10]*(2 - 3*x[11]) + 2*x[11])*x[12] + (2*x[11]*(3 - 4*x[12]) + x[10]*(6 - 8*x[12] + x[11]*(-9 + 6*x[12])))*x[9] + x[8]*(x[11]*(6 - 5*x[12] + (-5 + 4*x[12])*x[9]) + x[10]*(6 - 5*x[12] + x[11]*(-9 + 6*x[12]) + (-5 - 3*x[11]*(-2 + x[12]) + 4*x[12])*x[9]))))) + x[4]*(x[7]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9] + x[8]*(x[11]*x[12]*(6 - 5*x[9]) + x[10]*(x[12]*(6 - 5*x[9]) + x[11]*(6 - 8*x[12] + (-5 + 4*x[12])*x[9])))) + x[6]*(6*x[10]*x[11]*x[12] + 6*x[10]*x[11]*x[9] + 6*x[10]*x[12]*x[9] + 6*x[11]*x[12]*x[9] - 5*x[10]*x[11]*x[12]*x[9] + x[8]*(x[11]*x[12]*(6 - 5*x[9]) + x[10]*(x[12]*(6 - 5*x[9]) + x[11]*(6 - 8*x[12] + (-5 + 4*x[12])*x[9]))) + x[7]*(3*(x[10]*(2 - 3*x[11]) + 2*x[11])*x[12] + (2*x[11]*(3 - 4*x[12]) + x[10]*(6 - 8*x[12] + x[11]*(-9 + 6*x[12])))*x[9] + x[8]*(x[11]*(6 - 5*x[12] + (-5 + 4*x[12])*x[9]) + x[10]*(6 - 5*x[12] + x[11]*(-9 + 6*x[12]) + (-5 - 3*x[11]*(-2 + x[12]) + 4*x[12])*x[9])))) + x[5]*(x[7]*((x[10]*(6 - 5*x[11]) + 6*x[11])*x[12] + (2*x[11]*(3 - 4*x[12]) + x[10]*(6 - 8*x[12] + x[11]*(-5 + 4*x[12])))*x[9] + x[8]*(x[11]*(6 - 9*x[12] + (-5 + 6*x[12])*x[9]) + x[10]*(6 - 9*x[12] + x[11]*(-5 + 6*x[12]) + (-5 + x[11]*(4 - 3*x[12]) + 6*x[12])*x[9]))) + x[6]*(x[12]*(2*x[11]*(3 - 4*x[7]) + x[10]*(6 - 5*x[11] + (-8 + 6*x[11])*x[7])) + (x[10]*(6 - 8*x[12] + x[11]*(-5 + 4*x[12]) + (x[11]*(6 - 4*x[12]) + 8*(-1 + x[12]))*x[7]) + 2*x[11]*(3 - 4*x[12] + 4*(-1 + x[12])*x[7]))*x[9] + x[8]*(x[11]*(6 - 9*x[12] + (-5 + 6*x[12])*x[9] + x[7]*(-8 + 6*x[12] + (6 - 4*x[12])*x[9])) + x[10]*(6 - 5*x[11] - 9*x[12] + 6*x[11]*x[12] + (-5 + x[11]*(4 - 3*x[12]) + 6*x[12])*x[9] + 2*x[7]*(-4 + x[11]*(3 - 2*x[12]) + 3*x[12] + (3 + x[11]*(-2 + x[12]) - 2*x[12])*x[9])))))))) + x[1]*(-(x[3]*(6*x[10]*x[11]*x[12]*x[5]*x[6] + 6*x[10]*x[11]*x[12]*x[5]*x[7] + 6*x[10]*x[11]*x[12]*x[6]*x[7] - 5*x[10]*x[11]*x[12]*x[5]*x[6]*x[7] + 6*x[10]*x[11]*x[12]*x[6]*x[8] + 6*x[10]*x[11]*x[5]*x[6]*x[8] - 8*x[10]*x[11]*x[12]*x[5]*x[6]*x[8] + 6*x[10]*x[11]*x[12]*x[7]*x[8] + 6*x[10]*x[11]*x[5]*x[7]*x[8] - 8*x[10]*x[11]*x[12]*x[5]*x[7]*x[8] + 6*x[10]*x[11]*x[6]*x[7]*x[8] - 5*x[10]*x[11]*x[12]*x[6]*x[7]*x[8] - 5*x[10]*x[11]*x[5]*x[6]*x[7]*x[8] + 4*x[10]*x[11]*x[12]*x[5]*x[6]*x[7]*x[8] + 6*x[10]*x[11]*x[5]*x[6]*x[9] + 6*x[10]*x[12]*x[5]*x[6]*x[9] + 6*x[11]*x[12]*x[5]*x[6]*x[9] - 5*x[10]*x[11]*x[12]*x[5]*x[6]*x[9] + 6*x[10]*x[11]*x[5]*x[7]*x[9] + 6*x[10]*x[12]*x[5]*x[7]*x[9] + 6*x[11]*x[12]*x[5]*x[7]*x[9] - 5*x[10]*x[11]*x[12]*x[5]*x[7]*x[9] + 6*x[10]*x[11]*x[6]*x[7]*x[9] + 6*x[10]*x[12]*x[6]*x[7]*x[9] + 6*x[11]*x[12]*x[6]*x[7]*x[9] - 5*x[10]*x[11]*x[12]*x[6]*x[7]*x[9] - 5*x[10]*x[11]*x[5]*x[6]*x[7]*x[9] - 5*x[10]*x[12]*x[5]*x[6]*x[7]*x[9] - 5*x[11]*x[12]*x[5]*x[6]*x[7]*x[9] + 4*x[10]*x[11]*x[12]*x[5]*x[6]*x[7]*x[9] + 6*x[10]*x[11]*x[6]*x[8]*x[9] + 6*x[10]*x[12]*x[6]*x[8]*x[9] + 6*x[11]*x[12]*x[6]*x[8]*x[9] - 5*x[10]*x[11]*x[12]*x[6]*x[8]*x[9] + 6*x[10]*x[5]*x[6]*x[8]*x[9] + 6*x[11]*x[5]*x[6]*x[8]*x[9] - 9*x[10]*x[11]*x[5]*x[6]*x[8]*x[9] - 8*x[10]*x[12]*x[5]*x[6]*x[8]*x[9] - 8*x[11]*x[12]*x[5]*x[6]*x[8]*x[9] + 6*x[10]*x[11]*x[12]*x[5]*x[6]*x[8]*x[9] + 6*x[10]*x[11]*x[7]*x[8]*x[9] + 6*x[10]*x[12]*x[7]*x[8]*x[9] + 6*x[11]*x[12]*x[7]*x[8]*x[9] - 5*x[10]*x[11]*x[12]*x[7]*x[8]*x[9] + 6*x[10]*x[5]*x[7]*x[8]*x[9] + 6*x[11]*x[5]*x[7]*x[8]*x[9] - 9*x[10]*x[11]*x[5]*x[7]*x[8]*x[9] - 8*x[10]*x[12]*x[5]*x[7]*x[8]*x[9] - 8*x[11]*x[12]*x[5]*x[7]*x[8]*x[9] + 6*x[10]*x[11]*x[12]*x[5]*x[7]*x[8]*x[9] + 6*x[10]*x[6]*x[7]*x[8]*x[9] + 6*x[11]*x[6]*x[7]*x[8]*x[9] - 8*x[10]*x[11]*x[6]*x[7]*x[8]*x[9] - 5*x[10]*x[12]*x[6]*x[7]*x[8]*x[9] - 5*x[11]*x[12]*x[6]*x[7]*x[8]*x[9] + 4*x[10]*x[11]*x[12]*x[6]*x[7]*x[8]*x[9] - 5*x[10]*x[5]*x[6]*x[7]*x[8]*x[9] - 5*x[11]*x[5]*x[6]*x[7]*x[8]*x[9] + 6*x[10]*x[11]*x[5]*x[6]*x[7]*x[8]*x[9] + 4*x[10]*x[12]*x[5]*x[6]*x[7]*x[8]*x[9] + 4*x[11]*x[12]*x[5]*x[6]*x[7]*x[8]*x[9] - 3*x[10]*x[11]*x[12]*x[5]*x[6]*x[7]*x[8]*x[9] + x[4]*(x[7]*(6*x[10]*x[11]*x[12] + (6*x[11]*x[12] + x[10]*(x[11]*(6 - 5*x[12]) + 6*x[12]))*x[9] + x[8]*(2*x[11]*x[12]*(3 - 4*x[9]) + x[10]*(2*x[12]*(3 - 4*x[9]) + x[11]*(6 - 9*x[12] + (-8 + 6*x[12])*x[9])))) + x[6]*(6*x[10]*x[11]*x[12] + 6*x[10]*x[11]*x[9] + 6*x[10]*x[12]*x[9] + 6*x[11]*x[12]*x[9] - 5*x[10]*x[11]*x[12]*x[9] + x[8]*(2*x[11]*x[12]*(3 - 4*x[9]) + x[10]*(2*x[12]*(3 - 4*x[9]) + x[11]*(6 - 9*x[12] + (-8 + 6*x[12])*x[9]))) + x[7]*(2*(x[10]*(3 - 4*x[11]) + 3*x[11])*x[12] + (3*x[11]*(2 - 3*x[12]) + x[10]*(6 - 9*x[12] + x[11]*(-8 + 6*x[12])))*x[9] + x[8]*(x[11]*(6 - 5*x[12] + (-8 + 6*x[12])*x[9]) + x[10]*(6 - 5*x[12] + x[11]*(-8 + 6*x[12]) + (-8 - 4*x[11]*(-2 + x[12]) + 6*x[12])*x[9])))) + x[5]*(x[7]*((x[10]*(6 - 5*x[11]) + 6*x[11])*x[12] + (2*x[11]*(3 - 4*x[12]) + x[10]*(6 - 8*x[12] + x[11]*(-5 + 4*x[12])))*x[9] + x[8]*(x[10]*(6 - 8*x[12] + x[11]*(-5 + 6*x[12]) + (x[11]*(6 - 4*x[12]) + 8*(-1 + x[12]))*x[9]) + 2*x[11]*(3 - 4*x[12] + 4*(-1 + x[12])*x[9]))) + x[6]*(x[12]*(x[11]*(6 - 5*x[7]) + x[10]*(6 - 5*x[11] + (-5 + 4*x[11])*x[7])) + (x[11]*(6 - 8*x[12] + (-5 + 6*x[12])*x[7]) + x[10]*(6 - 8*x[12] + x[11]*(-5 + 4*x[12]) + (-5 + x[11]*(4 - 3*x[12]) + 6*x[12])*x[7]))*x[9] + x[8]*(x[11]*(6 - 8*x[12] + 8*(-1 + x[12])*x[9] + x[7]*(-5 + 4*x[12] + (6 - 4*x[12])*x[9])) + x[10]*(6 - 5*x[11] - 8*x[12] + 6*x[11]*x[12] + (x[11]*(6 - 4*x[12]) + 8*(-1 + x[12]))*x[9] + x[7]*(-5 + x[11]*(4 - 3*x[12]) + 4*x[12] + 2*(3 + x[11]*(-2 + x[12]) - 2*x[12])*x[9])))))))) + x[2]*(-6*x[10]*x[11]*x[12]*x[4]*x[6] - 6*x[10]*x[11]*x[12]*x[5]*x[6] - 6*x[10]*x[12]*x[4]*x[5]*x[6] - 6*x[11]*x[12]*x[4]*x[5]*x[6] + 5*x[10]*x[11]*x[12]*x[4]*x[5]*x[6] - 6*x[10]*x[11]*x[12]*x[4]*x[7] - 6*x[10]*x[11]*x[12]*x[5]*x[7] - 6*x[10]*x[12]*x[4]*x[5]*x[7] - 6*x[11]*x[12]*x[4]*x[5]*x[7] + 5*x[10]*x[11]*x[12]*x[4]*x[5]*x[7] - 6*x[10]*x[11]*x[12]*x[6]*x[7] - 6*x[10]*x[12]*x[4]*x[6]*x[7] - 6*x[11]*x[12]*x[4]*x[6]*x[7] + 8*x[10]*x[11]*x[12]*x[4]*x[6]*x[7] + 5*x[10]*x[11]*x[12]*x[5]*x[6]*x[7] + 5*x[10]*x[12]*x[4]*x[5]*x[6]*x[7] + 5*x[11]*x[12]*x[4]*x[5]*x[6]*x[7] - 4*x[10]*x[11]*x[12]*x[4]*x[5]*x[6]*x[7] - 6*x[10]*x[11]*x[12]*x[6]*x[8] - 6*x[10]*x[11]*x[4]*x[6]*x[8] - 6*x[10]*x[12]*x[4]*x[6]*x[8] - 6*x[11]*x[12]*x[4]*x[6]*x[8] + 9*x[10]*x[11]*x[12]*x[4]*x[6]*x[8] - 6*x[10]*x[11]*x[5]*x[6]*x[8] + 8*x[10]*x[11]*x[12]*x[5]*x[6]*x[8] - 6*x[10]*x[4]*x[5]*x[6]*x[8] - 6*x[11]*x[4]*x[5]*x[6]*x[8] + 5*x[10]*x[11]*x[4]*x[5]*x[6]*x[8] + 8*x[10]*x[12]*x[4]*x[5]*x[6]*x[8] + 8*x[11]*x[12]*x[4]*x[5]*x[6]*x[8] - 6*x[10]*x[11]*x[12]*x[4]*x[5]*x[6]*x[8] - 6*x[10]*x[11]*x[12]*x[7]*x[8] - 6*x[10]*x[11]*x[4]*x[7]*x[8] - 6*x[10]*x[12]*x[4]*x[7]*x[8] - 6*x[11]*x[12]*x[4]*x[7]*x[8] + 9*x[10]*x[11]*x[12]*x[4]*x[7]*x[8] - 6*x[10]*x[11]*x[5]*x[7]*x[8] + 8*x[10]*x[11]*x[12]*x[5]*x[7]*x[8] - 6*x[10]*x[4]*x[5]*x[7]*x[8] - 6*x[11]*x[4]*x[5]*x[7]*x[8] + 5*x[10]*x[11]*x[4]*x[5]*x[7]*x[8] + 8*x[10]*x[12]*x[4]*x[5]*x[7]*x[8] + 8*x[11]*x[12]*x[4]*x[5]*x[7]*x[8] - 6*x[10]*x[11]*x[12]*x[4]*x[5]*x[7]*x[8] - 6*x[10]*x[11]*x[6]*x[7]*x[8] + 5*x[10]*x[11]*x[12]*x[6]*x[7]*x[8] - 6*x[10]*x[4]*x[6]*x[7]*x[8] - 6*x[11]*x[4]*x[6]*x[7]*x[8] + 8*x[10]*x[11]*x[4]*x[6]*x[7]*x[8] + 5*x[10]*x[12]*x[4]*x[6]*x[7]*x[8] + 5*x[11]*x[12]*x[4]*x[6]*x[7]*x[8] - 6*x[10]*x[11]*x[12]*x[4]*x[6]*x[7]*x[8] + 5*x[10]*x[11]*x[5]*x[6]*x[7]*x[8] - 4*x[10]*x[11]*x[12]*x[5]*x[6]*x[7]*x[8] + 5*x[10]*x[4]*x[5]*x[6]*x[7]*x[8] + 5*x[11]*x[4]*x[5]*x[6]*x[7]*x[8] - 4*x[10]*x[11]*x[4]*x[5]*x[6]*x[7]*x[8] - 4*x[10]*x[12]*x[4]*x[5]*x[6]*x[7]*x[8] - 4*x[11]*x[12]*x[4]*x[5]*x[6]*x[7]*x[8] + 3*x[10]*x[11]*x[12]*x[4]*x[5]*x[6]*x[7]*x[8] - 6*x[10]*x[11]*x[4]*x[6]*x[9] - 6*x[10]*x[12]*x[4]*x[6]*x[9] - 6*x[11]*x[12]*x[4]*x[6]*x[9] + 5*x[10]*x[11]*x[12]*x[4]*x[6]*x[9] - 6*x[10]*x[11]*x[5]*x[6]*x[9] - 6*x[10]*x[12]*x[5]*x[6]*x[9] - 6*x[11]*x[12]*x[5]*x[6]*x[9] + 5*x[10]*x[11]*x[12]*x[5]*x[6]*x[9] - 6*x[10]*x[4]*x[5]*x[6]*x[9] - 6*x[11]*x[4]*x[5]*x[6]*x[9] + 5*x[10]*x[11]*x[4]*x[5]*x[6]*x[9] + 8*x[10]*x[12]*x[4]*x[5]*x[6]*x[9] + 8*x[11]*x[12]*x[4]*x[5]*x[6]*x[9] - 4*x[10]*x[11]*x[12]*x[4]*x[5]*x[6]*x[9] - 6*x[10]*x[11]*x[4]*x[7]*x[9] - 6*x[10]*x[12]*x[4]*x[7]*x[9] - 6*x[11]*x[12]*x[4]*x[7]*x[9] + 5*x[10]*x[11]*x[12]*x[4]*x[7]*x[9] - 6*x[10]*x[11]*x[5]*x[7]*x[9] - 6*x[10]*x[12]*x[5]*x[7]*x[9] - 6*x[11]*x[12]*x[5]*x[7]*x[9] + 5*x[10]*x[11]*x[12]*x[5]*x[7]*x[9] - 6*x[10]*x[4]*x[5]*x[7]*x[9] - 6*x[11]*x[4]*x[5]*x[7]*x[9] + 5*x[10]*x[11]*x[4]*x[5]*x[7]*x[9] + 8*x[10]*x[12]*x[4]*x[5]*x[7]*x[9] + 8*x[11]*x[12]*x[4]*x[5]*x[7]*x[9] - 4*x[10]*x[11]*x[12]*x[4]*x[5]*x[7]*x[9] - 6*x[10]*x[11]*x[6]*x[7]*x[9] - 6*x[10]*x[12]*x[6]*x[7]*x[9] - 6*x[11]*x[12]*x[6]*x[7]*x[9] + 5*x[10]*x[11]*x[12]*x[6]*x[7]*x[9] - 6*x[10]*x[4]*x[6]*x[7]*x[9] - 6*x[11]*x[4]*x[6]*x[7]*x[9] + 8*x[10]*x[11]*x[4]*x[6]*x[7]*x[9] + 9*x[10]*x[12]*x[4]*x[6]*x[7]*x[9] + 9*x[11]*x[12]*x[4]*x[6]*x[7]*x[9] - 6*x[10]*x[11]*x[12]*x[4]*x[6]*x[7]*x[9] + 5*x[10]*x[11]*x[5]*x[6]*x[7]*x[9] + 5*x[10]*x[12]*x[5]*x[6]*x[7]*x[9] + 5*x[11]*x[12]*x[5]*x[6]*x[7]*x[9] - 4*x[10]*x[11]*x[12]*x[5]*x[6]*x[7]*x[9] + 5*x[10]*x[4]*x[5]*x[6]*x[7]*x[9] + 5*x[11]*x[4]*x[5]*x[6]*x[7]*x[9] - 4*x[10]*x[11]*x[4]*x[5]*x[6]*x[7]*x[9] - 6*x[10]*x[12]*x[4]*x[5]*x[6]*x[7]*x[9] - 6*x[11]*x[12]*x[4]*x[5]*x[6]*x[7]*x[9] + 3*x[10]*x[11]*x[12]*x[4]*x[5]*x[6]*x[7]*x[9] - 6*x[10]*x[11]*x[6]*x[8]*x[9] - 6*x[10]*x[12]*x[6]*x[8]*x[9] - 6*x[11]*x[12]*x[6]*x[8]*x[9] + 5*x[10]*x[11]*x[12]*x[6]*x[8]*x[9] + 8*x[10]*x[11]*x[4]*x[6]*x[8]*x[9] + 8*x[10]*x[12]*x[4]*x[6]*x[8]*x[9] + 8*x[11]*x[12]*x[4]*x[6]*x[8]*x[9] - 6*x[10]*x[11]*x[12]*x[4]*x[6]*x[8]*x[9] - 6*x[10]*x[5]*x[6]*x[8]*x[9] - 6*x[11]*x[5]*x[6]*x[8]*x[9] + 9*x[10]*x[11]*x[5]*x[6]*x[8]*x[9] + 8*x[10]*x[12]*x[5]*x[6]*x[8]*x[9] + 8*x[11]*x[12]*x[5]*x[6]*x[8]*x[9] - 6*x[10]*x[11]*x[12]*x[5]*x[6]*x[8]*x[9] + 8*x[10]*x[4]*x[5]*x[6]*x[8]*x[9] + 8*x[11]*x[4]*x[5]*x[6]*x[8]*x[9] - 6*x[10]*x[11]*x[4]*x[5]*x[6]*x[8]*x[9] - 8*x[10]*x[12]*x[4]*x[5]*x[6]*x[8]*x[9] - 8*x[11]*x[12]*x[4]*x[5]*x[6]*x[8]*x[9] + 4*x[10]*x[11]*x[12]*x[4]*x[5]*x[6]*x[8]*x[9] - 6*x[10]*x[11]*x[7]*x[8]*x[9] - 6*x[10]*x[12]*x[7]*x[8]*x[9] - 6*x[11]*x[12]*x[7]*x[8]*x[9] + 5*x[10]*x[11]*x[12]*x[7]*x[8]*x[9] + 8*x[10]*x[11]*x[4]*x[7]*x[8]*x[9] + 8*x[10]*x[12]*x[4]*x[7]*x[8]*x[9] + 8*x[11]*x[12]*x[4]*x[7]*x[8]*x[9] - 6*x[10]*x[11]*x[12]*x[4]*x[7]*x[8]*x[9] - 6*x[10]*x[5]*x[7]*x[8]*x[9] - 6*x[11]*x[5]*x[7]*x[8]*x[9] + 9*x[10]*x[11]*x[5]*x[7]*x[8]*x[9] + 8*x[10]*x[12]*x[5]*x[7]*x[8]*x[9] + 8*x[11]*x[12]*x[5]*x[7]*x[8]*x[9] - 6*x[10]*x[11]*x[12]*x[5]*x[7]*x[8]*x[9] + 8*x[10]*x[4]*x[5]*x[7]*x[8]*x[9] + 8*x[11]*x[4]*x[5]*x[7]*x[8]*x[9] - 6*x[10]*x[11]*x[4]*x[5]*x[7]*x[8]*x[9] - 8*x[10]*x[12]*x[4]*x[5]*x[7]*x[8]*x[9] - 8*x[11]*x[12]*x[4]*x[5]*x[7]*x[8]*x[9] + 4*x[10]*x[11]*x[12]*x[4]*x[5]*x[7]*x[8]*x[9] - 6*x[10]*x[6]*x[7]*x[8]*x[9] - 6*x[11]*x[6]*x[7]*x[8]*x[9] + 8*x[10]*x[11]*x[6]*x[7]*x[8]*x[9] + 5*x[10]*x[12]*x[6]*x[7]*x[8]*x[9] + 5*x[11]*x[12]*x[6]*x[7]*x[8]*x[9] - 4*x[10]*x[11]*x[12]*x[6]*x[7]*x[8]*x[9] + 8*x[10]*x[4]*x[6]*x[7]*x[8]*x[9] + 8*x[11]*x[4]*x[6]*x[7]*x[8]*x[9] - 8*x[10]*x[11]*x[4]*x[6]*x[7]*x[8]*x[9] - 6*x[10]*x[12]*x[4]*x[6]*x[7]*x[8]*x[9] - 6*x[11]*x[12]*x[4]*x[6]*x[7]*x[8]*x[9] + 4*x[10]*x[11]*x[12]*x[4]*x[6]*x[7]*x[8]*x[9] + 5*x[10]*x[5]*x[6]*x[7]*x[8]*x[9] + 5*x[11]*x[5]*x[6]*x[7]*x[8]*x[9] - 6*x[10]*x[11]*x[5]*x[6]*x[7]*x[8]*x[9] - 4*x[10]*x[12]*x[5]*x[6]*x[7]*x[8]*x[9] - 4*x[11]*x[12]*x[5]*x[6]*x[7]*x[8]*x[9] + 3*x[10]*x[11]*x[12]*x[5]*x[6]*x[7]*x[8]*x[9] - 6*x[10]*x[4]*x[5]*x[6]*x[7]*x[8]*x[9] - 6*x[11]*x[4]*x[5]*x[6]*x[7]*x[8]*x[9] + 4*x[10]*x[11]*x[4]*x[5]*x[6]*x[7]*x[8]*x[9] + 4*x[10]*x[12]*x[4]*x[5]*x[6]*x[7]*x[8]*x[9] + 4*x[11]*x[12]*x[4]*x[5]*x[6]*x[7]*x[8]*x[9] - 2*x[10]*x[11]*x[12]*x[4]*x[5]*x[6]*x[7]*x[8]*x[9] + x[3]*(x[7]*(x[10]*x[11]*x[12]*(-6 + 5*x[4]) + (x[11]*x[12]*(-6 + 5*x[4]) + x[10]*(x[12]*(-6 + 5*x[4]) + x[11]*(-6 + 5*x[12] + (5 - 4*x[12])*x[4])))*x[9] + x[8]*(x[11]*x[12]*(-6 + x[4]*(5 - 4*x[9]) + 5*x[9]) + x[10]*(x[12]*(-6 + x[4]*(5 - 4*x[9]) + 5*x[9]) + x[11]*(-6 + 8*x[12] + (5 - 4*x[12])*x[9] + x[4]*(5 - 6*x[12] + (-4 + 3*x[12])*x[9]))))) + x[6]*(-6*x[10]*x[11]*x[12] + 5*x[10]*x[11]*x[12]*x[4] - 6*x[10]*x[11]*x[9] - 6*x[10]*x[12]*x[9] - 6*x[11]*x[12]*x[9] + 5*x[10]*x[11]*x[12]*x[9] + 5*x[10]*x[11]*x[4]*x[9] + 5*x[10]*x[12]*x[4]*x[9] + 5*x[11]*x[12]*x[4]*x[9] - 4*x[10]*x[11]*x[12]*x[4]*x[9] + x[8]*(x[11]*x[12]*(-6 + x[4]*(5 - 4*x[9]) + 5*x[9]) + x[10]*(x[12]*(-6 + x[4]*(5 - 4*x[9]) + 5*x[9]) + x[11]*(-6 + 8*x[12] + (5 - 4*x[12])*x[9] + x[4]*(5 - 6*x[12] + (-4 + 3*x[12])*x[9])))) + x[7]*(x[12]*(x[11]*(-6 + 5*x[4]) + x[10]*(-6 + 9*x[11] + (5 - 6*x[11])*x[4])) + (x[11]*(-6 + 8*x[12] + (5 - 6*x[12])*x[4]) + x[10]*(-6 + x[11]*(9 - 6*x[12]) + 8*x[12] + (5 - 6*x[12] + x[11]*(-6 + 4*x[12]))*x[4]))*x[9] + x[8]*(x[11]*(-6 + 5*x[12] + (5 - 4*x[12])*x[9] + x[4]*(5 - 4*x[12] + (-4 + 3*x[12])*x[9])) + x[10]*(-6 + 9*x[11] + 5*x[12] - 6*x[11]*x[12] + (5 + 3*x[11]*(-2 + x[12]) - 4*x[12])*x[9] + x[4]*(5 - 4*x[12] + x[11]*(-6 + 4*x[12]) + (-4 - 2*x[11]*(-2 + x[12]) + 3*x[12])*x[9]))))) + x[5]*(x[7]*(x[12]*(x[11]*(-6 + 5*x[4]) + x[10]*(-6 + 8*x[11] + (5 - 4*x[11])*x[4])) + (x[11]*(-6 + 9*x[12] + (5 - 6*x[12])*x[4]) + x[10]*(-6 + x[11]*(8 - 6*x[12]) + 9*x[12] + (5 - 6*x[12] + x[11]*(-4 + 3*x[12]))*x[4]))*x[9] + x[8]*(x[10]*(-6 + 8*x[11] + 8*x[12] - 8*x[11]*x[12] + (5 - 6*x[12] + x[11]*(-6 + 4*x[12]))*x[9] + x[4]*(5 + 4*x[11]*(-1 + x[12]) - 6*x[12] + (x[11]*(3 - 2*x[12]) + 4*(-1 + x[12]))*x[9])) + x[11]*(-6 + 8*x[12] + (5 - 6*x[12])*x[9] + x[4]*(5 - 6*x[12] + 4*(-1 + x[12])*x[9])))) + x[6]*(x[12]*(x[11]*(-6 + x[4]*(5 - 4*x[7]) + 5*x[7]) + x[10]*(-6 + 8*x[11] + (5 - 6*x[11])*x[7] + x[4]*(5 - 4*x[11] + (-4 + 3*x[11])*x[7]))) + (x[10]*(-6 + 8*x[11] + 9*x[12] - 6*x[11]*x[12] + (5 - 6*x[12] + x[11]*(-6 + 4*x[12]))*x[7] + x[4]*(5 - 6*x[12] + x[11]*(-4 + 3*x[12]) + (x[11]*(3 - 2*x[12]) + 4*(-1 + x[12]))*x[7])) + x[11]*(-6 + 9*x[12] + (5 - 6*x[12])*x[7] + x[4]*(5 - 6*x[12] + 4*(-1 + x[12])*x[7])))*x[9] + x[8]*(x[11]*(-6 + 8*x[12] + 5*x[9] - 6*x[12]*x[9] + x[7]*(5 - 4*x[12] + (-4 + 3*x[12])*x[9]) + x[4]*(5 - 6*x[12] + 4*(-1 + x[12])*x[9] + x[7]*(-4 + 3*x[12] + (3 - 2*x[12])*x[9]))) + x[10]*(-6 + 8*x[11] + 8*x[12] - 8*x[11]*x[12] + 5*x[9] - 6*x[11]*x[9] - 6*x[12]*x[9] + 4*x[11]*x[12]*x[9] + x[7]*(5 - 4*x[12] + x[11]*(-6 + 4*x[12]) + (-4 - 2*x[11]*(-2 + x[12]) + 3*x[12])*x[9]) + x[4]*(5 - 4*x[11] - 6*x[12] + 4*x[11]*x[12] + (x[11]*(3 - 2*x[12]) + 4*(-1 + x[12]))*x[9] + x[7]*(-4 + x[11]*(3 - 2*x[12]) + 3*x[12] + (3 + x[11]*(-2 + x[12]) - 2*x[12])*x[9])))))))));
}
