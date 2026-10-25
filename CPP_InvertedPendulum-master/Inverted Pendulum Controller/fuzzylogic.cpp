#include <algorithm>
#include "fuzzylogic.h"

/////////////////////////////////////////////////////////////////

//Initialise Fuzzy Rules

void initFuzzyRules(fuzzy_system_rec *fl)
{
    //----------------------------------------------------------------------------
    // Regions for X (x/x-dot) and Y (theta/theta-dot):
    //                    X          
    //            NL  NS  ZE  PS  PL 
    //            ___________________
    //       NL  |NL      NL      NS 
    //       NS  |    NM      NS     
    //   Y   ZE  |NM      ZE      PM 
    //       PS  |    PS      PM     
    //       PL  |PS      PL      PL 

    for (int rule_no = 0; rule_no < 13; rule_no++)
    {
        fl->rules[rule_no].inp_index[0] = in_x;
        fl->rules[rule_no].inp_index[1] = in_y;
    }

    fl->rules[0].inp_fuzzy_set[0] = in_nl;
    fl->rules[0].inp_fuzzy_set[1] = in_nl;
    fl->rules[0].out_fuzzy_set = out_nl;
    fl->rules[1].inp_fuzzy_set[0] = in_nl;
    fl->rules[1].inp_fuzzy_set[1] = in_ze;
    //fl->rules[1].out_fuzzy_set = out_nvl;
    fl->rules[1].out_fuzzy_set = out_nm;
    fl->rules[2].inp_fuzzy_set[0] = in_nl;
    fl->rules[2].inp_fuzzy_set[1] = in_pl;
    fl->rules[2].out_fuzzy_set = out_ps;

    fl->rules[3].inp_fuzzy_set[0] = in_ns;
    fl->rules[3].inp_fuzzy_set[1] = in_ns;
    fl->rules[3].out_fuzzy_set = out_nm;
    fl->rules[4].inp_fuzzy_set[0] = in_ns;
    fl->rules[4].inp_fuzzy_set[1] = in_ps;
    fl->rules[4].out_fuzzy_set = out_ps;

    fl->rules[5].inp_fuzzy_set[0] = in_ze;
    fl->rules[5].inp_fuzzy_set[1] = in_nl;
    fl->rules[5].out_fuzzy_set = out_nl;
    fl->rules[6].inp_fuzzy_set[0] = in_ze;
    fl->rules[6].inp_fuzzy_set[1] = in_ze;
    fl->rules[6].out_fuzzy_set = out_ze;
    fl->rules[7].inp_fuzzy_set[0] = in_ze;
    fl->rules[7].inp_fuzzy_set[1] = in_pl;
    fl->rules[7].out_fuzzy_set = out_pl;

    fl->rules[8].inp_fuzzy_set[0] = in_ps;
    fl->rules[8].inp_fuzzy_set[1] = in_ns;
    fl->rules[8].out_fuzzy_set = out_ns;
    fl->rules[9].inp_fuzzy_set[0] = in_ps;
    fl->rules[9].inp_fuzzy_set[1] = in_ps;
    fl->rules[9].out_fuzzy_set = out_pm;

    fl->rules[10].inp_fuzzy_set[0] = in_pl;
    fl->rules[10].inp_fuzzy_set[1] = in_nl;
    fl->rules[10].out_fuzzy_set = out_ns;
    fl->rules[11].inp_fuzzy_set[0] = in_pl;
    fl->rules[11].inp_fuzzy_set[1] = in_ze;
    //fl->rules[11].out_fuzzy_set = out_pvl;
    fl->rules[11].out_fuzzy_set = out_pm;
    fl->rules[12].inp_fuzzy_set[0] = in_pl;
    fl->rules[12].inp_fuzzy_set[1] = in_pl;
    fl->rules[12].out_fuzzy_set = out_pl;

    /*//----------------------------------------------------------------------------
    // Regions for X (x/x-dot) and Y (theta/theta-dot):
    //                    X          
    //            NL  NS  ZE  PS  PL 
    //            ___________________
    //       NL  |NL      NM      NS 
    //       NS  |    NM      NS     
    //   Y   ZE  |NS      ZE      PS 
    //       PS  |    PS      PM     
    //       PL  |PS      PM      PL 

    for (int rule_no = 0; rule_no < 25; rule_no++)
    {
        // Rules for looking at theta/theta-dot input values.
        fl->rules[rule_no].inp_index[0] = in_x;
        fl->rules[rule_no].inp_index[1] = in_y;
    }

    fl->rules[0].inp_fuzzy_set[0] = in_nl;
    fl->rules[0].inp_fuzzy_set[1] = in_nl;
    fl->rules[0].out_fuzzy_set = out_nl;
    fl->rules[1].inp_fuzzy_set[0] = in_nl;
    fl->rules[1].inp_fuzzy_set[1] = in_ns;
    fl->rules[1].out_fuzzy_set = out_ze;
    fl->rules[2].inp_fuzzy_set[0] = in_nl;
    fl->rules[2].inp_fuzzy_set[1] = in_ze;
    fl->rules[2].out_fuzzy_set = out_ns;
    fl->rules[3].inp_fuzzy_set[0] = in_nl;
    fl->rules[3].inp_fuzzy_set[1] = in_ps;
    fl->rules[3].out_fuzzy_set = out_ze;
    fl->rules[4].inp_fuzzy_set[0] = in_nl;
    fl->rules[4].inp_fuzzy_set[1] = in_pl;
    fl->rules[4].out_fuzzy_set = out_ps;

    fl->rules[5].inp_fuzzy_set[0] = in_ns;
    fl->rules[5].inp_fuzzy_set[1] = in_nl;
    fl->rules[5].out_fuzzy_set = out_ze;
    fl->rules[6].inp_fuzzy_set[0] = in_ns;
    fl->rules[6].inp_fuzzy_set[1] = in_ns;
    fl->rules[6].out_fuzzy_set = out_nm;
    fl->rules[7].inp_fuzzy_set[0] = in_ns;
    fl->rules[7].inp_fuzzy_set[1] = in_ze;
    fl->rules[7].out_fuzzy_set = out_ze;
    fl->rules[8].inp_fuzzy_set[0] = in_ns;
    fl->rules[8].inp_fuzzy_set[1] = in_ps;
    fl->rules[8].out_fuzzy_set = out_ps;
    fl->rules[9].inp_fuzzy_set[0] = in_ns;
    fl->rules[9].inp_fuzzy_set[1] = in_pl;
    fl->rules[9].out_fuzzy_set = out_ze;

    fl->rules[10].inp_fuzzy_set[0] = in_ze;
    fl->rules[10].inp_fuzzy_set[1] = in_nl;
    fl->rules[10].out_fuzzy_set = out_nm;
    fl->rules[11].inp_fuzzy_set[0] = in_ze;
    fl->rules[11].inp_fuzzy_set[1] = in_ns;
    fl->rules[11].out_fuzzy_set = out_ze;
    fl->rules[12].inp_fuzzy_set[0] = in_ze;
    fl->rules[12].inp_fuzzy_set[1] = in_ze;
    fl->rules[12].out_fuzzy_set = out_ze;
    fl->rules[13].inp_fuzzy_set[0] = in_ze;
    fl->rules[13].inp_fuzzy_set[1] = in_ps;
    fl->rules[13].out_fuzzy_set = out_ze;
    fl->rules[14].inp_fuzzy_set[0] = in_ze;
    fl->rules[14].inp_fuzzy_set[1] = in_pl;
    fl->rules[14].out_fuzzy_set = out_pm;

    fl->rules[15].inp_fuzzy_set[0] = in_ps;
    fl->rules[15].inp_fuzzy_set[1] = in_nl;
    fl->rules[15].out_fuzzy_set = out_ze;
    fl->rules[16].inp_fuzzy_set[0] = in_ps;
    fl->rules[16].inp_fuzzy_set[1] = in_ns;
    fl->rules[16].out_fuzzy_set = out_ns;
    fl->rules[17].inp_fuzzy_set[0] = in_ps;
    fl->rules[17].inp_fuzzy_set[1] = in_ze;
    fl->rules[17].out_fuzzy_set = out_ze;
    fl->rules[18].inp_fuzzy_set[0] = in_ps;
    fl->rules[18].inp_fuzzy_set[1] = in_ps;
    fl->rules[18].out_fuzzy_set = out_pm;
    fl->rules[19].inp_fuzzy_set[0] = in_ps;
    fl->rules[19].inp_fuzzy_set[1] = in_pl;
    fl->rules[19].out_fuzzy_set = out_ze;

    fl->rules[20].inp_fuzzy_set[0] = in_pl;
    fl->rules[20].inp_fuzzy_set[1] = in_nl;
    fl->rules[20].out_fuzzy_set = out_ns;
    fl->rules[21].inp_fuzzy_set[0] = in_pl;
    fl->rules[21].inp_fuzzy_set[1] = in_ns;
    fl->rules[21].out_fuzzy_set = out_ze;
    fl->rules[22].inp_fuzzy_set[0] = in_pl;
    fl->rules[22].inp_fuzzy_set[1] = in_ze;
    fl->rules[22].out_fuzzy_set = out_ps;
    fl->rules[23].inp_fuzzy_set[0] = in_pl;
    fl->rules[23].inp_fuzzy_set[1] = in_ps;
    fl->rules[23].out_fuzzy_set = out_ze;
    fl->rules[24].inp_fuzzy_set[0] = in_pl;
    fl->rules[24].inp_fuzzy_set[1] = in_pl;
    fl->rules[24].out_fuzzy_set = out_pl;*/

    // Before looking at Fig. 29. (a) from Yamakawa's paper
    /*//----------------------------------------------------------------------------
    // Regions for x (x/x-dot) and y (theta/theta-dot):
    //                    X          
    //            NL  NS  ZE  PS  PL 
    //            ___________________
    //       NL  |NVL NVL NL  NM  NM 
    //       NS  |NL  NL  NM  NS  NM 
    //   Y   ZE  |PM  PL  ZE  NL  NM 
    //       PS  |PM  PS  PM  PL  PL 
    //       PL  |PM  PM  PL  PVL PVL

    for (int rule_no = 0; rule_no < 25; rule_no++)
    {
        // Rules for looking at theta/theta-dot input values.
        fl->rules[rule_no].inp_index[0] = in_x;
        fl->rules[rule_no].inp_index[1] = in_y;
    }

    fl->rules[0].inp_fuzzy_set[0] = in_nl;
    fl->rules[0].inp_fuzzy_set[1] = in_nl;
    fl->rules[0].out_fuzzy_set = out_nvl;
    fl->rules[1].inp_fuzzy_set[0] = in_nl;
    fl->rules[1].inp_fuzzy_set[1] = in_ns;
    fl->rules[1].out_fuzzy_set = out_nl;
    fl->rules[2].inp_fuzzy_set[0] = in_nl;
    fl->rules[2].inp_fuzzy_set[1] = in_ze;
    fl->rules[2].out_fuzzy_set = out_pm;
    fl->rules[3].inp_fuzzy_set[0] = in_nl;
    fl->rules[3].inp_fuzzy_set[1] = in_ps;
    fl->rules[3].out_fuzzy_set = out_pm;
    fl->rules[4].inp_fuzzy_set[0] = in_nl;
    fl->rules[4].inp_fuzzy_set[1] = in_pl;
    fl->rules[4].out_fuzzy_set = out_pm;

    fl->rules[5].inp_fuzzy_set[0] = in_ns;
    fl->rules[5].inp_fuzzy_set[1] = in_nl;
    fl->rules[5].out_fuzzy_set = out_nvl;
    fl->rules[6].inp_fuzzy_set[0] = in_ns;
    fl->rules[6].inp_fuzzy_set[1] = in_ns;
    fl->rules[6].out_fuzzy_set = out_nl;
    fl->rules[7].inp_fuzzy_set[0] = in_ns;
    fl->rules[7].inp_fuzzy_set[1] = in_ze;
    fl->rules[7].out_fuzzy_set = out_pl;
    fl->rules[8].inp_fuzzy_set[0] = in_ns;
    fl->rules[8].inp_fuzzy_set[1] = in_ps;
    fl->rules[8].out_fuzzy_set = out_ps;
    fl->rules[9].inp_fuzzy_set[0] = in_ns;
    fl->rules[9].inp_fuzzy_set[1] = in_pl;
    fl->rules[9].out_fuzzy_set = out_pm;

    fl->rules[10].inp_fuzzy_set[0] = in_ze;
    fl->rules[10].inp_fuzzy_set[1] = in_nl;
    fl->rules[10].out_fuzzy_set = out_nl;
    fl->rules[11].inp_fuzzy_set[0] = in_ze;
    fl->rules[11].inp_fuzzy_set[1] = in_ns;
    fl->rules[11].out_fuzzy_set = out_nm;
    fl->rules[12].inp_fuzzy_set[0] = in_ze;
    fl->rules[12].inp_fuzzy_set[1] = in_ze;
    fl->rules[12].out_fuzzy_set = out_ze;
    fl->rules[13].inp_fuzzy_set[0] = in_ze;
    fl->rules[13].inp_fuzzy_set[1] = in_ps;
    fl->rules[13].out_fuzzy_set = out_pm;
    fl->rules[14].inp_fuzzy_set[0] = in_ze;
    fl->rules[14].inp_fuzzy_set[1] = in_pl;
    fl->rules[14].out_fuzzy_set = out_pl;

    fl->rules[15].inp_fuzzy_set[0] = in_ps;
    fl->rules[15].inp_fuzzy_set[1] = in_nl;
    fl->rules[15].out_fuzzy_set = out_nm;
    fl->rules[16].inp_fuzzy_set[0] = in_ps;
    fl->rules[16].inp_fuzzy_set[1] = in_ns;
    fl->rules[16].out_fuzzy_set = out_ns;
    fl->rules[17].inp_fuzzy_set[0] = in_ps;
    fl->rules[17].inp_fuzzy_set[1] = in_ze;
    fl->rules[17].out_fuzzy_set = out_nl;
    fl->rules[18].inp_fuzzy_set[0] = in_ps;
    fl->rules[18].inp_fuzzy_set[1] = in_ps;
    fl->rules[18].out_fuzzy_set = out_pl;
    fl->rules[19].inp_fuzzy_set[0] = in_ps;
    fl->rules[19].inp_fuzzy_set[1] = in_pl;
    fl->rules[19].out_fuzzy_set = out_pvl;

    fl->rules[20].inp_fuzzy_set[0] = in_pl;
    fl->rules[20].inp_fuzzy_set[1] = in_nl;
    fl->rules[20].out_fuzzy_set = out_nm;
    fl->rules[21].inp_fuzzy_set[0] = in_pl;
    fl->rules[21].inp_fuzzy_set[1] = in_ns;
    fl->rules[21].out_fuzzy_set = out_nm;
    fl->rules[22].inp_fuzzy_set[0] = in_pl;
    fl->rules[22].inp_fuzzy_set[1] = in_ze;
    fl->rules[22].out_fuzzy_set = out_nm;
    fl->rules[23].inp_fuzzy_set[0] = in_pl;
    fl->rules[23].inp_fuzzy_set[1] = in_ps;
    fl->rules[23].out_fuzzy_set = out_pl;
    fl->rules[24].inp_fuzzy_set[0] = in_pl;
    fl->rules[24].inp_fuzzy_set[1] = in_pl;
    fl->rules[24].out_fuzzy_set = out_pvl;*/

    // Before using Yamakawa's technique to combine x/x-dot etc.
    /*const int no_of_x_rules = 25;
    const int no_of_theta_rules = 25;

    //----------------------------------------------------------------------------     
    // THETA vs. THETA_DOT    
    // 
    // Regions for theta and theta_dot:
    //                      THETA       
    //               NL  NS  ZE  PS  PL 
    //                ___________________
    //           NL  |NVL NL  NL  NM  NM 
    //           NS  |NL  NM  NS  NS  PS 
    // THETA-DOT ZE  |NM  NS  ZE  PS  PM 
    //           PS  |NS  PS  PS  PM  PL 
    //           PL  |PM  PM  PL  PL  PVL

    // int inp_theta_set_no = 0;                                       // The set number that theta belongs to, see enum for fuzzy sets.
    // int inp_theta_dot_set_no = 0;                                   // The set number that theta-dot belongs to, see enum for fuzzy sets.             
    // int out_term_no = 8;                                            // The output term for the rule, see enum for output terms.

    // for (int rule_no = 0; rule_no < no_of_theta_rules; rule_no++)
    // {
    //     // Rules for looking at theta/theta-dot input values.
    //     fl->rules[rule_no].inp_index[0] = in_theta;
    //     fl->rules[rule_no].inp_index[1] = in_theta_dot;

    //     // Calculate values for sets/terms.
    //     inp_theta_set_no = rule_no / 5;
    //     inp_theta_dot_set_no = rule_no % 5;
    //     out_term_no = inp_theta_set_no + inp_theta_dot_set_no;

    //     // Set regions for theta/theta-dot.
    //     fl->rules[rule_no].inp_fuzzy_set[0] = inp_theta_set_no;
    //     fl->rules[rule_no].inp_fuzzy_set[1] = inp_theta_dot_set_no;
    //     fl->rules[rule_no].out_fuzzy_set = out_term_no;
    // }

    for (int rule_no = 0; rule_no < no_of_theta_rules; rule_no++)
    {
        // Rules for looking at theta/theta-dot input values.
        fl->rules[rule_no].inp_index[0] = in_theta;
        fl->rules[rule_no].inp_index[1] = in_theta_dot;
    }

    fl->rules[0].inp_fuzzy_set[0] = in_nl;
    fl->rules[0].inp_fuzzy_set[1] = in_nl;
    fl->rules[0].out_fuzzy_set = out_nvl;
    fl->rules[1].inp_fuzzy_set[0] = in_nl;
    fl->rules[1].inp_fuzzy_set[1] = in_ns;
    fl->rules[1].out_fuzzy_set = out_nl;
    fl->rules[2].inp_fuzzy_set[0] = in_nl;
    fl->rules[2].inp_fuzzy_set[1] = in_ze;
    fl->rules[2].out_fuzzy_set = out_nm;
    fl->rules[3].inp_fuzzy_set[0] = in_nl;
    fl->rules[3].inp_fuzzy_set[1] = in_ps;
    fl->rules[3].out_fuzzy_set = out_ns;
    fl->rules[4].inp_fuzzy_set[0] = in_nl;
    fl->rules[4].inp_fuzzy_set[1] = in_pl;
    fl->rules[4].out_fuzzy_set = out_pm;

    fl->rules[5].inp_fuzzy_set[0] = in_ns;
    fl->rules[5].inp_fuzzy_set[1] = in_nl;
    fl->rules[5].out_fuzzy_set = out_nl;
    fl->rules[6].inp_fuzzy_set[0] = in_ns;
    fl->rules[6].inp_fuzzy_set[1] = in_ns;
    fl->rules[6].out_fuzzy_set = out_nm;
    fl->rules[7].inp_fuzzy_set[0] = in_ns;
    fl->rules[7].inp_fuzzy_set[1] = in_ze;
    fl->rules[7].out_fuzzy_set = out_ns;
    fl->rules[8].inp_fuzzy_set[0] = in_ns;
    fl->rules[8].inp_fuzzy_set[1] = in_ps;
    fl->rules[8].out_fuzzy_set = out_ps;
    fl->rules[9].inp_fuzzy_set[0] = in_ns;
    fl->rules[9].inp_fuzzy_set[1] = in_pl;
    fl->rules[9].out_fuzzy_set = out_pm;

    fl->rules[10].inp_fuzzy_set[0] = in_ze;
    fl->rules[10].inp_fuzzy_set[1] = in_nl;
    fl->rules[10].out_fuzzy_set = out_nl;
    fl->rules[11].inp_fuzzy_set[0] = in_ze;
    fl->rules[11].inp_fuzzy_set[1] = in_ns;
    fl->rules[11].out_fuzzy_set = out_ns;
    fl->rules[12].inp_fuzzy_set[0] = in_ze;
    fl->rules[12].inp_fuzzy_set[1] = in_ze;
    fl->rules[12].out_fuzzy_set = out_ze;
    fl->rules[13].inp_fuzzy_set[0] = in_ze;
    fl->rules[13].inp_fuzzy_set[1] = in_ps;
    fl->rules[13].out_fuzzy_set = out_ps;
    fl->rules[14].inp_fuzzy_set[0] = in_ze;
    fl->rules[14].inp_fuzzy_set[1] = in_pl;
    fl->rules[14].out_fuzzy_set = out_pl;

    fl->rules[15].inp_fuzzy_set[0] = in_ps;
    fl->rules[15].inp_fuzzy_set[1] = in_nl;
    fl->rules[15].out_fuzzy_set = out_nm;
    fl->rules[16].inp_fuzzy_set[0] = in_ps;
    fl->rules[16].inp_fuzzy_set[1] = in_ns;
    fl->rules[16].out_fuzzy_set = out_ns;
    fl->rules[17].inp_fuzzy_set[0] = in_ps;
    fl->rules[17].inp_fuzzy_set[1] = in_ze;
    fl->rules[17].out_fuzzy_set = out_ps;
    fl->rules[18].inp_fuzzy_set[0] = in_ps;
    fl->rules[18].inp_fuzzy_set[1] = in_ps;
    fl->rules[18].out_fuzzy_set = out_pm;
    fl->rules[19].inp_fuzzy_set[0] = in_ps;
    fl->rules[19].inp_fuzzy_set[1] = in_pl;
    fl->rules[19].out_fuzzy_set = out_pl;

    fl->rules[20].inp_fuzzy_set[0] = in_pl;
    fl->rules[20].inp_fuzzy_set[1] = in_nl;
    fl->rules[20].out_fuzzy_set = out_nm;
    fl->rules[21].inp_fuzzy_set[0] = in_pl;
    fl->rules[21].inp_fuzzy_set[1] = in_ns;
    fl->rules[21].out_fuzzy_set = out_ps;
    fl->rules[22].inp_fuzzy_set[0] = in_pl;
    fl->rules[22].inp_fuzzy_set[1] = in_ze;
    fl->rules[22].out_fuzzy_set = out_pm;
    fl->rules[23].inp_fuzzy_set[0] = in_pl;
    fl->rules[23].inp_fuzzy_set[1] = in_ps;
    fl->rules[23].out_fuzzy_set = out_pl;
    fl->rules[24].inp_fuzzy_set[0] = in_pl;
    fl->rules[24].inp_fuzzy_set[1] = in_pl;
    fl->rules[24].out_fuzzy_set = out_pvl;

    //----------------------------------------------------------------------------   
    //X vs. X_DOT
    //
    // Regions for x and x_dot:
    //                     X         
    //            NL  NS  ZE  PS  PL 
    //            ___________________
    //       NL  |PVL PL  PM  PS  ZE 
    //       NS  |PL  PM  PS  ZE  NS 
    // X-DOT ZE  |PM  PS  ZE  NS  NM 
    //       PS  |PS  ZE  NS  NM  NL 
    //       PL  |ZE  NS  NM  NL  NVL

    int inp_x_set_no = 0;                                           // The set number that X belongs to, see enum for fuzzy sets.
    int inp_x_dot_set_no = 0;                                       // The set number that X-dot belongs to, see enum for fuzzy sets.             
    int out_term_no = 8;                                            // The output term for the rule, see enum for output terms.

    for (int rule_no = no_of_theta_rules; rule_no < no_of_theta_rules + no_of_x_rules; rule_no++)
    {
        // Rules for looking at theta/theta-dot input values.
        fl->rules[rule_no].inp_index[0] = in_x;
        fl->rules[rule_no].inp_index[1] = in_x_dot;

        // Calculate values for sets/terms.
        inp_x_set_no = (rule_no - no_of_theta_rules) / 5;
        inp_x_dot_set_no = rule_no % 5;
        out_term_no = 8 - (inp_x_set_no + inp_x_dot_set_no);

        // Set regions for theta/theta-dot.
        fl->rules[rule_no].inp_fuzzy_set[0] = inp_x_set_no;
        fl->rules[rule_no].inp_fuzzy_set[1] = inp_x_dot_set_no;
        fl->rules[rule_no].out_fuzzy_set = out_term_no;
    }*/

    return;
}


void initMembershipFunctions(fuzzy_system_rec *fl)
{
    // X membership function (x/x-dot)
    // -2 < x < 2, -4 < x-dot < 4
    // X = 0.7(x) + 0.3(x-dot)
    // Therefore can expect: -2.6 < X < 2.6
    int input_no = in_x;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -2.6, -1.3, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-2.6, -1.3, -1.3, 0, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-1.3, 0, 0, 1.3, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(0, 1.3, 1.3, 2.6, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(1.3, 2.6, 0, 0, right_trapezoid);

    /*// -3 < x < 3, -5 < x-dot < 5
    // X = 0.8(x) + 0.2(x-dot)
    // Therefore can expect: -4.2 < X < 4.2
    int input_no = in_x;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -3.4, -1.7, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-3.4, -1.7, -1.7, -0, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-1.7, -0, 0, 1.7, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(0, 1.7, 1.7, 3.4, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(1.7, 3.4, 0, 0, right_trapezoid);*/
    /*// -2.5 < x < 2.5, -4 < x-dot < 4
    // X = 0.3(x) + 0.7(x-dot)
    // Therefore can expect: -3.55 < X < 3.55
    int input_no = in_x;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -3.55, -1.775, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-3.55, -1.775, -1.775, -0, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-1.775, -0, 0, 1.775, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(0, 1.775, 1.775, 3.55, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(1.775, 3.55, 0, 0, right_trapezoid);*/
    /*// -3 < x < 3, -5 < x-dot < 5
    // X = 0.3(x) + 0.7(x-dot)
    // Therefore can expect: -4.4 < X < 4.4
    int input_no = in_x;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -4.4, -2.2, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-4.4, -2.2, -2.2, -0, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-2.2, -0, 0, 2.2, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(0, 2.2, 2.2, 4.4, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(2.2, 4.4, 0, 0, right_trapezoid);*/
    /*// -3 < x < 3, -5 < x-dot < 5
    // X = 0.6(x) + 0.4(x-dot)
    // Therefore can expect: -3.8 < X < 3.8
    int input_no = in_x;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -3.8, -1.9, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-3.8, -1.9, -1.9, -0, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-1.9, -0, 0, 1.9, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(0, 1.9, 1.9, 3.8, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(1.9, 3.8, 0, 0, right_trapezoid);*/


    // Y membership function (theta/theta-dot)
    // -0.4 < theta < 0.4, -0.5 < theta-dot < 0.5
    // Y = 0.8(theta) + 0.2(theta-dot)
    // Therefore: -0.42 < Y < 0.42
    input_no = in_y;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -0.42, -0.21, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-0.42, -0.21, -0.21, 0, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-0.21, 0, 0, 0.21, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(0, 0.21, 0.21, 0.42, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(0.21, 0.42, 0, 0, right_trapezoid);

    /*// Y membership function (theta/theta-dot)
    // -0.8 < theta < 0.8, -1 < theta-dot < 1
    // Y = 0.8(theta) + 0.2(theta-dot)
    // Therefore: -0.84 < Y < 0.84
    input_no = in_y;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -0.84, -0.42, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-0.84, -0.42, -0.42, 0, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-0.42, 0, 0, 0.42, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(0, 0.42, 0.42, 0.84, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(0.42, 0.84, 0, 0, right_trapezoid);*/

    /*// -0.8 < theta < 0.8, -1 < theta-dot < 1
    // Y = 0.3(theta) + 0.7(theta-dot)
    // Therefore: -0.94 < Y < 0.94
    input_no = in_y;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -0.94, -0.47, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-0.94, -0.47, -0.47, -0, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-0.47, -0, 0, 0.47, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(0, 0.47, 0.47, 0.94, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(0.47, 0.94, 0, 0, right_trapezoid);*/
    /*// -0.8 < theta < 0.8, -1 < theta-dot < 1
    // Y = 0.6(theta) + 0.4(theta-dot)
    // Therefore: -0.88 < Y < 0.88
    input_no = in_y;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -0.88, -0.44, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-0.88, -0.44, -0.44, -0, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-0.44, -0, 0, 0.44, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(0, 0.44, 0.44, 0.88, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(0.44, 0.88, 0, 0, right_trapezoid);*/



    // Before using Yamakawa's technique
    /*// theta membership function
    int input_no = in_theta;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -0.6, -0.45, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-0.6, -0.45, -0.15, 0, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-0.2, -0.05, 0.05, 0.2, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(-0, 0.15, 0.45, 0.6, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(0.45, 0.6, 0, 0, right_trapezoid);

    // theta-dot membership function
    input_no = in_theta_dot;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -0.4, -0.25, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-0.4, -0.25, -0.1, 0.05, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-0.1, 0.05, 0.05, 0.1, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(-0.05, 0.1, 0.25, 0.4, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(0.25, 0.4, 0, 0, right_trapezoid);


    // X membership function
    input_no = in_x;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -2, -1.75, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-2, -1.5, -1, -0.5, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-1, -0.5, 0.5, 1, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(0.5, 1, 1.5, 2, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(1.75, 2, 0, 0, right_trapezoid);

    // X-dot membership function
    input_no = in_x_dot;
    fl->inp_mem_fns[input_no][in_nl] = init_trapz(0, 0, -4.5, -3.5, left_trapezoid);
    fl->inp_mem_fns[input_no][in_ns] = init_trapz(-4, -3, -2, -1, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ze] = init_trapz(-1.5, -0.75, 0.75, 1.5, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_ps] = init_trapz(1, 2, 3, 4, regular_trapezoid);
    fl->inp_mem_fns[input_no][in_pl] = init_trapz(3.5, 4.5, 0, 0, right_trapezoid);*/

    return;
}

void initFuzzySystem(fuzzy_system_rec *fl)
{
    //Note: The settings of these parameters will depend upon your fuzzy system design
    fl->no_of_inputs = 2;  /* Inputs are handled 2 at a time only */
    fl->no_of_rules = 13;
    fl->no_of_inp_regions = 5;
    fl->no_of_outputs = 7;

    // Before using Yamakawa's technique
    /*//Note: The settings of these parameters will depend upon your fuzzy system design
    fl->no_of_inputs = 2;   Inputs are handled 2 at a time only 
    fl->no_of_rules = 50;
    fl->no_of_inp_regions = 5;
    fl->no_of_outputs = 9;*/


    // Output values
    //fl->output_values[out_nvl]= - 100.0;
    fl->output_values[out_nl] = - 100.0;
    fl->output_values[out_nm] = - 80.0;
    fl->output_values[out_ns] = - 60.0;
    fl->output_values[out_ze] =    0.0;
    fl->output_values[out_ps] =   60.0;
    fl->output_values[out_pm] =   80.0;
    fl->output_values[out_pl] =   100.0;
    //fl->output_values[out_pvl]=   100.0;


    fl->rules = (rule *)malloc((size_t)(fl->no_of_rules * sizeof(rule)));
    initFuzzyRules(fl);
    initMembershipFunctions(fl);
    return;
}

//////////////////////////////////////////////////////////////////////////////

trapezoid init_trapz(float x1, float x2, float x3, float x4, trapz_type typ)
{
    trapezoid trz;
    trz.a = x1;
    trz.b = x2;
    trz.c = x3;
    trz.d = x4;
    trz.tp = typ;

    switch (trz.tp)
    {
        case regular_trapezoid:
            trz.l_slope = 1.0 / (trz.b - trz.a);
            trz.r_slope = 1.0 / (trz.c - trz.d);
            break;

        case left_trapezoid:
            trz.r_slope = 1.0 / (trz.a - trz.b);
            trz.l_slope = 0.0;
            break;

        case right_trapezoid:
            trz.l_slope = 1.0 / (trz.b - trz.a);
            trz.r_slope = 0.0;
            break;
    } /* end switch  */

    return trz;
}   /* end function */

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
float trapz(float x, trapezoid trz)
{
    switch (trz.tp)
    {
        case left_trapezoid:
            if (x <= trz.a)
            {
                return 1.0;
            }
            else if (x >= trz.b)
            {
                return 0.0;
            }
            else
            {
                /* a < x < b */
                return trz.r_slope * (x - trz.b);
            }


        case right_trapezoid:
            if (x <= trz.a)
            {
                return 0.0;
            }
            else if (x >= trz.b)
            {
                return 1.0;
            }
            else
            {
                /* a < x < b */
                return trz.l_slope * (x - trz.a);
            }

        case regular_trapezoid:
            if ((x <= trz.a) || (x >= trz.d))
            {
                return 0.0;
            }
            else if ((x >= trz.b) && (x <= trz.c))
            {
                return 1.0;
            }
            else if ((x >= trz.a) && (x <= trz.b))
            {
                return trz.l_slope * (x - trz.a);
            }
            else if ((x >= trz.c) && (x <= trz.d))
            {
                return  trz.r_slope * (x - trz.d);
            }

    }  /* End switch  */

    return 0.0;  /* should not get to this point */
}  /* End function */

//////////////////////////////////////////////////////////////////////////////
float min_of(float values[], int no_of_inps)
{
    int i;
    float val;
    val = values[0];
    for (i = 1; i < no_of_inps; i++)
    {
        if (values[i] < val)
        {
            val = values[i];
        }
    }
    return val;
}



//////////////////////////////////////////////////////////////////////////////
float fuzzy_system(float inputs[], fuzzy_system_rec fz)
{
    int i, j;
    short variable_index, fuzzy_set;
    float sum1 = 0.0, sum2 = 0.0, weight;
    float m_values[MAX_NO_OF_INPUTS];


    for (i = 0; i < fz.no_of_rules; i++)
    {
        for (j = 0; j < fz.no_of_inputs; j++)
        {
            variable_index = fz.rules[i].inp_index[j];
            fuzzy_set = fz.rules[i].inp_fuzzy_set[j];
            m_values[j] = trapz(inputs[variable_index],
                fz.inp_mem_fns[variable_index][fuzzy_set]);
        } /* end j  */

        weight = min_of(m_values, fz.no_of_inputs);

        sum1 += weight * fz.output_values[fz.rules[i].out_fuzzy_set];
        sum2 += weight;
    } /* end i  */


    if (fabs(sum2) < TOO_SMALL)
    {
        cout << "\r\nFLPRCS Error: Sum2 in fuzzy_system is 0.  Press key: " << endl;
        //~ getch();
        //~ exit(1);
        return 0.0;
    }

    return (sum1 / sum2);
}  /* end fuzzy_system  */

//////////////////////////////////////////////////////////////////////////////
void free_fuzzy_rules(fuzzy_system_rec *fz)
{
    if (fz->allocated)
    {
        free(fz->rules);
    }

    fz->allocated = false;
    return;
}

