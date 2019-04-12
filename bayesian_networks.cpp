#include "bits/stdc++.h"
using namespace std;
// 0 - corresponds to HIGH/GOOD
// 1 - corresponds to LOW/BAD
double F[2];
double CA[2];
double PROF[2][2];
double Fo[2][2];
double H[2][2];
double Faci[2][2];
double L[2][2];
double Assn[2][2];
double RW[2][2][2];
double PGCC[2];
double Life[2][2][2][2][2];
double Fut[2][2][2][2][2];
double J[2][2][2][2];

void test_probLife(){
    int Q;
    cin >> Q;
    while(Q--){
        int A, B, C, D, E;
        cin >> A >> B >> C >> D >> E;
        cout << Life[A][B][C][D][E] << endl;
    }
}


void test_probFut(){
    int Q;
    cin >> Q;
    while(Q--){
        int A, B, C, D, E;
        cin >> A >> B >> C >> D >> E;
        cout << Fut[A][B][C][D][E] << endl;
    }
}

void test_probJ(){
    int Q;
    cin >> Q;
    while(Q--){
        int A, B, C, D;
        cin >> A >> B >> C >> D;
        cout << J[A][B][C][D] << endl;
    }
}


int main()
{
    ifstream file("inp.in");
    /* Hard Coded */
    F[0] = 0.5; F[1] = 0.5;
    CA[0] = 0.35; CA[1] = 0.65;
    PROF[0][0] = 0.75; PROF[0][1] = 0.25; PROF[1][0] = 0.4; PROF[1][1] = 0.6;
    Fo[0][0] =  0.8; Fo[0][1] = 0.2; Fo[1][0] = 0.3; Fo[1][1] = 0.7;
    H[0][0] = 0.8; H[0][1] = 0.2; H[1][0] = 0.2; H[1][1] = 0.8;
    Faci[0][0] = 0.8; Faci[0][1] = 0.2; Faci[1][0] = 0.3; Faci[1][1] = 0.7;
    L[0][0] = 0.8; L[0][1] = 0.2; L[1][0] = 0.1; L[1][1] = 0.9;
    Assn[0][0] = 0.9; Assn[0][1] = 0.1; Assn[1][0] = 0.2; Assn[1][1] = 0.8;
    RW[0][0][0] = 0.95; RW[0][0][1] = 0.05; RW[0][1][0] = 0.1; RW[0][1][1] = 0.9;
    RW[1][0][0] = 0.4; RW[1][0][1] = 0.6; RW[1][1][0] = 0.05; RW[1][1][1] = 0.95;
    PGCC[0] = 0.7; PGCC[1] = 0.3;
    /* Assign probabilities from file */
    for(int i = 0; i < 32; ++i){
        file >> Life[((((1 << 4) & i) == 0) ? 0 : 1)][((((1 << 3) & i) == 0) ? 0 : 1)][((((1 << 2) & i) == 0) ? 0 : 1)][((((1 << 1) & i) == 0) ? 0 : 1)][((((1 << 0) & i) == 0) ? 0 : 1)];
    }
    for(int i = 0; i < 32; ++i){
        file >> Fut[((((1 << 4) & i) == 0) ? 0 : 1)][((((1 << 3) & i) == 0) ? 0 : 1)][((((1 << 2) & i) == 0) ? 0 : 1)][((((1 << 1) & i) == 0) ? 0 : 1)][((((1 << 0) & i) == 0) ? 0 : 1)];
    }
    for(int i = 0; i < 16; ++i){
        file >> J[((((1 << 3) & i) == 0) ? 0 : 1)][((((1 << 2) & i) == 0) ? 0 : 1)][((((1 << 1) & i) == 0) ? 0 : 1)][((((1 << 0) & i) == 0) ? 0 : 1)];
    }
    //test_probJ();
    //test_probFut();
    //test_probLife();
    double res = 0.0;
    for(int _F = 0; _F <= 1; ++_F){
        for(int _Fo = 0; _Fo <= 1; ++_Fo){
            for(int _CA = 0; _CA <= 1; ++_CA){
                for(int _H = 0; _H <= 1; ++_H){
                    for(int _Faci = 0; _Faci <= 1; ++_Faci){
                        for(int _Life = 0; _Life <= 1; ++_Life){
                            for(int _J = 0; _J <= 1; ++_J){
                                for(int _Fut = 0; _Fut <= 1; ++_Fut){
                                    for(int _PGCC = 0; _PGCC <= 1; ++_PGCC){
                                        for(int _RW = 0; _RW <= 1; ++_RW){
                                            for(int _L = 0; _L <= 1; ++_L){
                                                for(int _Assn = 0; _Assn <= 1; ++_Assn){
                                                    for(int _PROF = 0; _PROF <= 1; ++_PROF){
                                                        res = res + (
                                                            F[_F] * CA[_CA] * PROF[_F][_PROF] * Fo[_F][_Fo] * H[_F][_H] *
                                                            Faci[_F][_Faci] * Life[_Fo][_CA][_H][_Faci][_Life] * L[_PROF][_L] *
                                                            Assn[_PROF][_Assn] * RW[_F][_PROF][_RW] * PGCC[_PGCC] *
                                                            Fut[_PGCC][_RW][_Assn][_L][_Fut] * J[_Life][_F][_Fut][_J]
                                                        );
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "Total probability: " << res << endl;
    cout << "QUERY1 P(J = “YES” | Fut = “GOOD”, PGCC = “GOOD”)" << endl;
    // Computing numerator
    double num = 0.0;
    for(int _F = 0; _F <= 1; ++_F){
        for(int _Fo = 0; _Fo <= 1; ++_Fo){
            for(int _CA = 0; _CA <= 1; ++_CA){
                for(int _H = 0; _H <= 1; ++_H){
                    for(int _Faci = 0; _Faci <= 1; ++_Faci){
                        for(int _Life = 0; _Life <= 1; ++_Life){
                            for(int _J = 0; _J <= 0; ++_J){
                                for(int _Fut = 0; _Fut <= 0; ++_Fut){
                                    for(int _PGCC = 0; _PGCC <= 0; ++_PGCC){
                                        for(int _RW = 0; _RW <= 1; ++_RW){
                                            for(int _L = 0; _L <= 1; ++_L){
                                                for(int _Assn = 0; _Assn <= 1; ++_Assn){
                                                    for(int _PROF = 0; _PROF <= 1; ++_PROF){
                                                        num = num + (
                                                            F[_F] * CA[_CA] * PROF[_F][_PROF] * Fo[_F][_Fo] * H[_F][_H] *
                                                            Faci[_F][_Faci] * Life[_Fo][_CA][_H][_Faci][_Life] * L[_PROF][_L] *
                                                            Assn[_PROF][_Assn] * RW[_F][_PROF][_RW] * PGCC[_PGCC] *
                                                            Fut[_PGCC][_RW][_Assn][_L][_Fut] * J[_Life][_F][_Fut][_J]
                                                        );
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "Numerator: " << num << endl;
    double den = 0.0;
    for(int _F = 0; _F <= 1; ++_F){
        for(int _Fo = 0; _Fo <= 1; ++_Fo){
            for(int _CA = 0; _CA <= 1; ++_CA){
                for(int _H = 0; _H <= 1; ++_H){
                    for(int _Faci = 0; _Faci <= 1; ++_Faci){
                        for(int _Life = 0; _Life <= 1; ++_Life){
                            for(int _J = 0; _J <= 1; ++_J){
                                for(int _Fut = 0; _Fut <= 0; ++_Fut){
                                    for(int _PGCC = 0; _PGCC <= 0; ++_PGCC){
                                        for(int _RW = 0; _RW <= 1; ++_RW){
                                            for(int _L = 0; _L <= 1; ++_L){
                                                for(int _Assn = 0; _Assn <= 1; ++_Assn){
                                                    for(int _PROF = 0; _PROF <= 1; ++_PROF){
                                                        den = den + (
                                                            F[_F] * CA[_CA] * PROF[_F][_PROF] * Fo[_F][_Fo] * H[_F][_H] *
                                                            Faci[_F][_Faci] * Life[_Fo][_CA][_H][_Faci][_Life] * L[_PROF][_L] *
                                                            Assn[_PROF][_Assn] * RW[_F][_PROF][_RW] * PGCC[_PGCC] *
                                                            Fut[_PGCC][_RW][_Assn][_L][_Fut] * J[_Life][_F][_Fut][_J]
                                                        );
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "Denominator: " << den << endl;
    cout << "Answer to query1: " << (num / den) << endl;

    /*****************************************************************************************************************************************/
    cout << "QUERY2 P(J = “NO” | Fut = “GOOD”, PGCC = “GOOD”)" << endl;
    // Computing numerator
    num = 0.0;
    for(int _F = 0; _F <= 1; ++_F){
        for(int _Fo = 0; _Fo <= 1; ++_Fo){
            for(int _CA = 0; _CA <= 1; ++_CA){
                for(int _H = 0; _H <= 1; ++_H){
                    for(int _Faci = 0; _Faci <= 1; ++_Faci){
                        for(int _Life = 0; _Life <= 1; ++_Life){
                            for(int _J = 1; _J <= 1; ++_J){
                                for(int _Fut = 0; _Fut <= 0; ++_Fut){
                                    for(int _PGCC = 0; _PGCC <= 0; ++_PGCC){
                                        for(int _RW = 0; _RW <= 1; ++_RW){
                                            for(int _L = 0; _L <= 1; ++_L){
                                                for(int _Assn = 0; _Assn <= 1; ++_Assn){
                                                    for(int _PROF = 0; _PROF <= 1; ++_PROF){
                                                        num = num + (
                                                            F[_F] * CA[_CA] * PROF[_F][_PROF] * Fo[_F][_Fo] * H[_F][_H] *
                                                            Faci[_F][_Faci] * Life[_Fo][_CA][_H][_Faci][_Life] * L[_PROF][_L] *
                                                            Assn[_PROF][_Assn] * RW[_F][_PROF][_RW] * PGCC[_PGCC] *
                                                            Fut[_PGCC][_RW][_Assn][_L][_Fut] * J[_Life][_F][_Fut][_J]
                                                        );
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "Numerator: " << num << endl;
    den = 0.0;
    for(int _F = 0; _F <= 1; ++_F){
        for(int _Fo = 0; _Fo <= 1; ++_Fo){
            for(int _CA = 0; _CA <= 1; ++_CA){
                for(int _H = 0; _H <= 1; ++_H){
                    for(int _Faci = 0; _Faci <= 1; ++_Faci){
                        for(int _Life = 0; _Life <= 1; ++_Life){
                            for(int _J = 0; _J <= 1; ++_J){
                                for(int _Fut = 0; _Fut <= 0; ++_Fut){
                                    for(int _PGCC = 0; _PGCC <= 0; ++_PGCC){
                                        for(int _RW = 0; _RW <= 1; ++_RW){
                                            for(int _L = 0; _L <= 1; ++_L){
                                                for(int _Assn = 0; _Assn <= 1; ++_Assn){
                                                    for(int _PROF = 0; _PROF <= 1; ++_PROF){
                                                        den = den + (
                                                            F[_F] * CA[_CA] * PROF[_F][_PROF] * Fo[_F][_Fo] * H[_F][_H] *
                                                            Faci[_F][_Faci] * Life[_Fo][_CA][_H][_Faci][_Life] * L[_PROF][_L] *
                                                            Assn[_PROF][_Assn] * RW[_F][_PROF][_RW] * PGCC[_PGCC] *
                                                            Fut[_PGCC][_RW][_Assn][_L][_Fut] * J[_Life][_F][_Fut][_J]
                                                        );
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "Denominator: " << den << endl;
    cout << "Answer to query2: " << (num / den) << endl;
    /********************************************************************************************************************************/
    cout << "QUERY3 P(J = “YES” | Fo = “GOOD”, F = “HIGH”) " << endl;
    // Computing numerator
    num = 0.0;
    for(int _F = 0; _F <= 0; ++_F){
        for(int _Fo = 0; _Fo <= 0; ++_Fo){
            for(int _CA = 0; _CA <= 1; ++_CA){
                for(int _H = 0; _H <= 1; ++_H){
                    for(int _Faci = 0; _Faci <= 1; ++_Faci){
                        for(int _Life = 0; _Life <= 1; ++_Life){
                            for(int _J = 0; _J <= 0; ++_J){
                                for(int _Fut = 0; _Fut <= 1; ++_Fut){
                                    for(int _PGCC = 0; _PGCC <= 1; ++_PGCC){
                                        for(int _RW = 0; _RW <= 1; ++_RW){
                                            for(int _L = 0; _L <= 1; ++_L){
                                                for(int _Assn = 0; _Assn <= 1; ++_Assn){
                                                    for(int _PROF = 0; _PROF <= 1; ++_PROF){
                                                        num = num + (
                                                            F[_F] * CA[_CA] * PROF[_F][_PROF] * Fo[_F][_Fo] * H[_F][_H] *
                                                            Faci[_F][_Faci] * Life[_Fo][_CA][_H][_Faci][_Life] * L[_PROF][_L] *
                                                            Assn[_PROF][_Assn] * RW[_F][_PROF][_RW] * PGCC[_PGCC] *
                                                            Fut[_PGCC][_RW][_Assn][_L][_Fut] * J[_Life][_F][_Fut][_J]
                                                        );
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "Numerator: " << num << endl;
    den = 0.0;
    for(int _F = 0; _F <= 0; ++_F){
        for(int _Fo = 0; _Fo <= 0; ++_Fo){
            for(int _CA = 0; _CA <= 1; ++_CA){
                for(int _H = 0; _H <= 1; ++_H){
                    for(int _Faci = 0; _Faci <= 1; ++_Faci){
                        for(int _Life = 0; _Life <= 1; ++_Life){
                            for(int _J = 0; _J <= 1; ++_J){
                                for(int _Fut = 0; _Fut <= 1; ++_Fut){
                                    for(int _PGCC = 0; _PGCC <= 1; ++_PGCC){
                                        for(int _RW = 0; _RW <= 1; ++_RW){
                                            for(int _L = 0; _L <= 1; ++_L){
                                                for(int _Assn = 0; _Assn <= 1; ++_Assn){
                                                    for(int _PROF = 0; _PROF <= 1; ++_PROF){
                                                        den = den + (
                                                            F[_F] * CA[_CA] * PROF[_F][_PROF] * Fo[_F][_Fo] * H[_F][_H] *
                                                            Faci[_F][_Faci] * Life[_Fo][_CA][_H][_Faci][_Life] * L[_PROF][_L] *
                                                            Assn[_PROF][_Assn] * RW[_F][_PROF][_RW] * PGCC[_PGCC] *
                                                            Fut[_PGCC][_RW][_Assn][_L][_Fut] * J[_Life][_F][_Fut][_J]
                                                        );
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "Denominator: " << den << endl;
    cout << "Answer to query2: " << (num / den) << endl;
    return 0;
}