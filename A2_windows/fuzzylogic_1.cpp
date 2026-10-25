#include <algorithm>
#include <vector>
#include "fuzzylogic.h"

/////////////////////////////////////////////////////////////////
//Initialise Fuzzy Rules 

void initFuzzyRules(fuzzy_system_rec *fl) {

   //using Yamakawa's paper

	
   const int
      no_of_x_rules = 25,
      no_of_theta_rules = 25;

   int i;
	
//---------------------------------------------------------------------------- 	
//THETA vs. THETA_DOT	
//FAMM for Theta vs. Theta_dot

//                      Theta
//                   NL  NS  ZE  PS  PL
//                ______________________
//              NL| NVL  NVL NVL NL  ZE
//              NS| NVL  NVL NL  ZE  PVL
// Theta_dot    ZE| NVL  NL  ZE  PVL PVL
//              PS| NL   ZE  PVL PVL PVL
//              PL| ZE   PVL PVL PVL PVL

//   vector<int> theta_FAMM = {
//       out_nvl, out_nvl, out_nvl, out_nl, out_ze,
// 		out_nvl, out_nvl, out_nl, out_ze, out_pvl,
// 		out_nvl, out_nl, out_ze, out_pvl, out_pvl,
// 		out_nl, out_ze, out_pvl, out_pvl, out_pvl,
// 		out_ze, out_pvl, out_pvl, out_pvl, out_pvl
//    };

//                      THETA       
   //               NL  NS  ZE  PS  PL 
   //                ___________________
   //           NL  |NVL NL  NL  NM  NM 
   //           NS  |NL  NM  NS  NS  PS 
   // THETA-DOT ZE  |NM  NS  ZE  PS  PM 
   //           PS  |NS  PS  PS  PM  PL 
   //           PL  |PM  PM  PL  PL  PVL

   vector<int> theta_FAMM = {
      out_nvl, out_nl, out_nl, out_nm, out_nm,
		out_nl, out_nm, out_ns, out_ns, out_ps,
		out_nm, out_ns, out_ze, out_ps, out_pm,
		out_ns, out_ps, out_ps, out_pm, out_pl,
		out_pm, out_pm, out_pl, out_pl, out_pvl
   };
     
   for (i = 0;i < no_of_theta_rules;i++) {
       fl->rules[i].inp_index[0] = in_theta;
       fl->rules[i].inp_index[1] = in_theta_dot;
       fl->rules[i].out_fuzzy_set = theta_FAMM[i];
   }
      
 //---------------------THETA VS. THETA_DOT INPUTs-----------------------//
 //--------------------------NEGATIVE_LARGE------------------------------//
   fl->rules[0].inp_fuzzy_set[0] = in_nl;
   fl->rules[0].inp_fuzzy_set[1] = in_nl;

   fl->rules[1].inp_fuzzy_set[0] = in_nl;
   fl->rules[1].inp_fuzzy_set[1] = in_ns;

   fl->rules[2].inp_fuzzy_set[0] = in_nl;
   fl->rules[2].inp_fuzzy_set[1] = in_ze;

   fl->rules[3].inp_fuzzy_set[0] = in_nl;
   fl->rules[3].inp_fuzzy_set[1] = in_ps;

   fl->rules[4].inp_fuzzy_set[0] = in_nl;
   fl->rules[4].inp_fuzzy_set[1] = in_pl;
//--------------------------NEGATIVE_SMALL------------------------------//
   fl->rules[5].inp_fuzzy_set[0] = in_ns;
   fl->rules[5].inp_fuzzy_set[1] = in_nl;

   fl->rules[6].inp_fuzzy_set[0] = in_ns;
   fl->rules[6].inp_fuzzy_set[1] = in_ns;

   fl->rules[7].inp_fuzzy_set[0] = in_ns;
   fl->rules[7].inp_fuzzy_set[1] = in_ze;

   fl->rules[8].inp_fuzzy_set[0] = in_ns;
   fl->rules[8].inp_fuzzy_set[1] = in_ps;

   fl->rules[9].inp_fuzzy_set[0] = in_ns;
   fl->rules[9].inp_fuzzy_set[1] = in_pl;
//-------------------------------ZERO----------------------------------//
   fl->rules[10].inp_fuzzy_set[0] = in_ze;
   fl->rules[10].inp_fuzzy_set[1] = in_ns;

   fl->rules[11].inp_fuzzy_set[0] = in_ze;
   fl->rules[11].inp_fuzzy_set[1] = in_ze;

   fl->rules[12].inp_fuzzy_set[0] = in_ze;
   fl->rules[12].inp_fuzzy_set[1] = in_ps;

   fl->rules[13].inp_fuzzy_set[0] = in_ze;
   fl->rules[13].inp_fuzzy_set[1] = in_pl;

   fl->rules[14].inp_fuzzy_set[0] = in_ze;
   fl->rules[14].inp_fuzzy_set[1] = in_nl;
//--------------------------POSITIVE_LARGE------------------------------//
   fl->rules[15].inp_fuzzy_set[0] = in_ps;
   fl->rules[15].inp_fuzzy_set[1] = in_nl;

   fl->rules[16].inp_fuzzy_set[0] = in_ps;
   fl->rules[16].inp_fuzzy_set[1] = in_ns;

   fl->rules[17].inp_fuzzy_set[0] = in_ps;
   fl->rules[17].inp_fuzzy_set[1] = in_ze;
   
   fl->rules[18].inp_fuzzy_set[0] = in_ps;
   fl->rules[18].inp_fuzzy_set[1] = in_ps;

   fl->rules[19].inp_fuzzy_set[0] = in_ps;
   fl->rules[19].inp_fuzzy_set[1] = in_pl;
//--------------------------POSITIVE_SMALL------------------------------//
   fl->rules[20].inp_fuzzy_set[0] = in_pl;
   fl->rules[20].inp_fuzzy_set[1] = in_nl;

   fl->rules[21].inp_fuzzy_set[0] = in_pl;
   fl->rules[21].inp_fuzzy_set[1] = in_ns;

   fl->rules[22].inp_fuzzy_set[0] = in_pl;
   fl->rules[22].inp_fuzzy_set[1] = in_ze;

   fl->rules[23].inp_fuzzy_set[0] = in_pl;
   fl->rules[23].inp_fuzzy_set[1] = in_ps;

   fl->rules[24].inp_fuzzy_set[0] = in_pl;
   fl->rules[24].inp_fuzzy_set[1] = in_pl;

   // //---------------------THETA VS. THETA_DOT OUTPUTs----------------------//
   // fl->rules[0].out_fuzzy_set = out_nvl;
	// fl->rules[1].out_fuzzy_set = out_nl;
   // fl->rules[2].out_fuzzy_set = out_nm;
   // fl->rules[3].out_fuzzy_set = out_ps;
   // fl->rules[4].out_fuzzy_set = out_pm;
   // fl->rules[5].out_fuzzy_set = out_nl;
   // fl->rules[6].out_fuzzy_set = out_nm;
   // fl->rules[7].out_fuzzy_set = out_ns;
   // fl->rules[8].out_fuzzy_set = out_ps;
   // fl->rules[9].out_fuzzy_set = out_pm;
   // fl->rules[10].out_fuzzy_set = out_nl;
   // fl->rules[11].out_fuzzy_set = out_ns;
   // fl->rules[12].out_fuzzy_set = out_ze;
   // fl->rules[13].out_fuzzy_set = out_ps;
   // fl->rules[14].out_fuzzy_set = out_pl;
   // fl->rules[15].out_fuzzy_set = out_nm;
   // fl->rules[16].out_fuzzy_set = out_ns;
   // fl->rules[17].out_fuzzy_set = out_ps;
   // fl->rules[18].out_fuzzy_set = out_pm;
   // fl->rules[19].out_fuzzy_set = out_pl;
   // fl->rules[20].out_fuzzy_set = out_nm;
   // fl->rules[21].out_fuzzy_set = out_ps;
   // fl->rules[22].out_fuzzy_set = out_pm;
   // fl->rules[23].out_fuzzy_set = out_pl;
   // fl->rules[24].out_fuzzy_set = out_pvl;
	
//----------------------------------------------------------------------------   
//X vs. X_DOT
//FAMM for X vs. X_dot

//                           X
//                   NL  NS  ZE  PS  PL
//                ______________________
//              NL| PVL  PL  PM  PS  ZE
//              NS| PL   PM  PS  ZE  NS
// X_dot        ZE| PM   PS  ZE  NS  NM
//              PS| PS   ZE  NS  NM  NL
//              PL| ZE   NS  NM  NL  NVL

   // vector<int> x_FAMM = {
	// 	out_pl, out_pl, out_pm, out_ps, out_ze,
	// 	out_pl, out_pm, out_ps, out_ze, out_ns,
	// 	out_pm, out_ps, out_ze, out_ns, out_nm,
	// 	out_ps, out_ze, out_ns, out_nm, out_nl,
	// 	out_ze, out_ns, out_nm, out_nl, out_nl
   // };

   // Regions for x and x_dot:
    //                     X         
    //            NL  NS  ZE  PS  PL 
    //            ___________________
    //       NL  |PVL PL  PM  PS  ZE 
    //       NS  |PL  PM  PS  ZE  NS 
    // X-DOT ZE  |PM  PS  ZE  NS  NM 
    //       PS  |PS  ZE  NS  NM  NL 
    //       PL  |ZE  NS  NM  NL  NVL

   vector<int> x_FAMM = {
		out_pvl, out_pl, out_pm, out_ps, out_ze,
		out_pl, out_pm, out_ps, out_ze, out_ns,
		out_pm, out_ps, out_ze, out_ns, out_nm,
		out_ps, out_ze, out_ns, out_nm, out_nl,
		out_ze, out_ns, out_nm, out_nl, out_nl
   };

   for (i = 0;i < no_of_x_rules;i++) {
   	  fl->rules[i + no_of_theta_rules].inp_index[0] = in_x;
   	  fl->rules[i + no_of_theta_rules].inp_index[1] = in_x_dot;
        fl->rules[i + no_of_theta_rules].out_fuzzy_set = x_FAMM[i];
	}
	  
//-------------------------X VS. X_Dot INPUTs---------------------------//
//--------------------------NEGATIVE_LARGE------------------------------//
   fl->rules[25+0].inp_fuzzy_set[0] = in_nl;
   fl->rules[25+0].inp_fuzzy_set[1] = in_nl;

   fl->rules[25+1].inp_fuzzy_set[0] = in_nl;
   fl->rules[25+1].inp_fuzzy_set[1] = in_ns;

   fl->rules[25+2].inp_fuzzy_set[0] = in_nl;
   fl->rules[25+2].inp_fuzzy_set[1] = in_ze;

   fl->rules[25+3].inp_fuzzy_set[0] = in_nl;
   fl->rules[25+3].inp_fuzzy_set[1] = in_ps;

   fl->rules[25+4].inp_fuzzy_set[0] = in_nl;
   fl->rules[25+4].inp_fuzzy_set[1] = in_pl;
//--------------------------NEGATIVE_SMALL------------------------------//
   fl->rules[25+5].inp_fuzzy_set[0] = in_ns;
   fl->rules[25+5].inp_fuzzy_set[1] = in_nl;

   fl->rules[25+6].inp_fuzzy_set[0] = in_ns;
   fl->rules[25+6].inp_fuzzy_set[1] = in_ns;

   fl->rules[25+7].inp_fuzzy_set[0] = in_ns;
   fl->rules[25+7].inp_fuzzy_set[1] = in_ze;

   fl->rules[25+8].inp_fuzzy_set[0] = in_ns;
   fl->rules[25+8].inp_fuzzy_set[1] = in_ps;

   fl->rules[25+9].inp_fuzzy_set[0] = in_ns;
   fl->rules[25+9].inp_fuzzy_set[1] = in_pl;
//-------------------------------ZERO----------------------------------//
   fl->rules[25+10].inp_fuzzy_set[0] = in_ze;
   fl->rules[25+10].inp_fuzzy_set[1] = in_nl;

   fl->rules[25+11].inp_fuzzy_set[0] = in_ze;
   fl->rules[25+11].inp_fuzzy_set[1] = in_ns;

   fl->rules[25+12].inp_fuzzy_set[0] = in_ze;
   fl->rules[25+12].inp_fuzzy_set[1] = in_ze;

   fl->rules[25+13].inp_fuzzy_set[0] = in_ze;
   fl->rules[25+13].inp_fuzzy_set[1] = in_ps;

   fl->rules[25+14].inp_fuzzy_set[0] = in_ze;
   fl->rules[25+14].inp_fuzzy_set[1] = in_pl;
//--------------------------POSITIVE_SMALL------------------------------//
   fl->rules[25+15].inp_fuzzy_set[0] = in_ps;
   fl->rules[25+15].inp_fuzzy_set[1] = in_nl;

   fl->rules[25+16].inp_fuzzy_set[0] = in_ps;
   fl->rules[25+16].inp_fuzzy_set[1] = in_ns;

   fl->rules[25+17].inp_fuzzy_set[0] = in_ps;
   fl->rules[25+17].inp_fuzzy_set[1] = in_ze;
   
   fl->rules[25+18].inp_fuzzy_set[0] = in_ps;
   fl->rules[25+18].inp_fuzzy_set[1] = in_ps;

   fl->rules[25+19].inp_fuzzy_set[0] = in_ps;
   fl->rules[25+19].inp_fuzzy_set[1] = in_pl;
//--------------------------POSITIVE_LARGE-----------------------------//
   fl->rules[25+20].inp_fuzzy_set[0] = in_pl;
   fl->rules[25+20].inp_fuzzy_set[1] = in_nl;

   fl->rules[25+21].inp_fuzzy_set[0] = in_pl;
   fl->rules[25+21].inp_fuzzy_set[1] = in_ns;

   fl->rules[25+22].inp_fuzzy_set[0] = in_pl;
   fl->rules[25+22].inp_fuzzy_set[1] = in_ze;

   fl->rules[25+23].inp_fuzzy_set[0] = in_pl;
   fl->rules[25+23].inp_fuzzy_set[1] = in_ps;

   fl->rules[25+24].inp_fuzzy_set[0] = in_pl;
   fl->rules[25+24].inp_fuzzy_set[1] = in_pl;
   
   //-------------------------X VS. X_Dot OUTPUTs--------------------------//
   // fl->rules[25+0].out_fuzzy_set = out_pvl;
	// fl->rules[25+1].out_fuzzy_set = out_pl;
   // fl->rules[25+2].out_fuzzy_set = out_pm;
   // fl->rules[25+3].out_fuzzy_set = out_ps;
   // fl->rules[25+4].out_fuzzy_set = out_ze;
   // fl->rules[25+5].out_fuzzy_set = out_pl;
   // fl->rules[25+6].out_fuzzy_set = out_pm;
   // fl->rules[25+7].out_fuzzy_set = out_ps;
   // fl->rules[25+8].out_fuzzy_set = out_ze;
   // fl->rules[25+9].out_fuzzy_set = out_ns;
   // fl->rules[25+10].out_fuzzy_set = out_pm;
   // fl->rules[25+11].out_fuzzy_set = out_ps;
   // fl->rules[25+12].out_fuzzy_set = out_ze;
   // fl->rules[25+13].out_fuzzy_set = out_ns;
   // fl->rules[25+14].out_fuzzy_set = out_nm;
   // fl->rules[25+15].out_fuzzy_set = out_ps;
   // fl->rules[25+16].out_fuzzy_set = out_ze;
   // fl->rules[25+17].out_fuzzy_set = out_ns;
   // fl->rules[25+18].out_fuzzy_set = out_nm;
   // fl->rules[25+19].out_fuzzy_set = out_nl;
   // fl->rules[25+20].out_fuzzy_set = out_ze;
   // fl->rules[25+21].out_fuzzy_set = out_ns;
   // fl->rules[25+22].out_fuzzy_set = out_nm;
   // fl->rules[25+23].out_fuzzy_set = out_nl;
   // fl->rules[25+24].out_fuzzy_set = out_nvl;

   return;
}


void initMembershipFunctions(fuzzy_system_rec *fl) {
	/*Modify manually got initialisation of membership function*/
   /* The X membership functions */
   float xa, xb, xc, xd, ya, yb, yc, yd;
   //x trapezoids
   xa=1.75;
   xb=1.25;
   xc=0.75;
   xd=0.25;

   //theta trapezoids
   ya=1.75;
   yb=1.25;
   yc=0.75;
   yd=0.25;
 
  	fl->inp_mem_fns[in_x][in_nl] = init_trapz (-xa,-xb, 0.0, 0.0, left_trapezoid);
   fl->inp_mem_fns[in_x][in_ns] = init_trapz (-xa,-xb, -xc, -xd, regular_trapezoid);
   fl->inp_mem_fns[in_x][in_ze] = init_trapz (-xc, -xd, xc, xd, regular_trapezoid);
   fl->inp_mem_fns[in_x][in_ps] = init_trapz (xd, xc, xb, xa, regular_trapezoid);
   fl->inp_mem_fns[in_x][in_pl] = init_trapz (xb, xc, 0.0, 0.0, right_trapezoid);

	
   /* The X dot membership functions */
   
  	fl->inp_mem_fns[in_x_dot][in_nl] = init_trapz (-xa,-xb, 0.0, 0.0, left_trapezoid);
   fl->inp_mem_fns[in_x_dot][in_ns] = init_trapz (-xa,-xb, -xc, -xd, regular_trapezoid);
   fl->inp_mem_fns[in_x_dot][in_ze] = init_trapz (-xc, -xd, xc, xd, regular_trapezoid);
   fl->inp_mem_fns[in_x_dot][in_ps] = init_trapz (xd, xc, xb, xa, regular_trapezoid);
   fl->inp_mem_fns[in_x_dot][in_pl] = init_trapz (xb, xc, 0.0, 0.0, right_trapezoid);

   /* The theta membership functions */

  	fl->inp_mem_fns[in_theta_dot][in_nl] = init_trapz (-ya,-yb, 0.0, 0.0, left_trapezoid);
   fl->inp_mem_fns[in_theta_dot][in_ns] = init_trapz (-ya,-yb, -yc, -yd, regular_trapezoid);
   fl->inp_mem_fns[in_theta_dot][in_ze] = init_trapz (-yc, -yd, yc, yd, regular_trapezoid);
   fl->inp_mem_fns[in_theta_dot][in_ps] = init_trapz (yd, yc, yb, ya, regular_trapezoid);
   fl->inp_mem_fns[in_theta_dot][in_pl] = init_trapz (yb, yc, 0.0, 0.0, right_trapezoid);
  	
   /* The theta dot membership functions */

  	fl->inp_mem_fns[in_theta][in_nl] = init_trapz (-ya,-yb, 0.0, 0.0, left_trapezoid);
   fl->inp_mem_fns[in_theta][in_ns] = init_trapz (-ya,-yb, -yc, -yd, regular_trapezoid);
   fl->inp_mem_fns[in_theta][in_ze] = init_trapz (-yc, -yd, yc, yd, regular_trapezoid);
   fl->inp_mem_fns[in_theta][in_ps] = init_trapz (yd, yc, yb, ya, regular_trapezoid);
   fl->inp_mem_fns[in_theta][in_pl] = init_trapz (yb, yc, 0.0, 0.0, right_trapezoid);

   return;
}

void initFuzzySystem (fuzzy_system_rec *fl) {

   // Note: The settings of these parameters will depend upon your fuzzy system design
   fl->no_of_inputs = 2;  /* Inputs are handled 2 at a time only */
   fl->no_of_rules = 50;
   fl->no_of_inp_regions = 5;
   fl->no_of_outputs = 9;

   float a, b, c, d;
   a=400;                           //very large
   b=200;                           //large
   c=100;                           //medium
   d=50;                            //small
	
   coefficient_A=0.0;               //Theta Coef.
   coefficient_B=0.0;               //Theta_dot coef.
   coefficient_C=0.0;               //X coef.
   coefficient_D=0.0;               //X_dot coef.
	
	// fl->output_values [out_nvvl] = -114.0;
   // fl->output_values [out_nvl] = -104.0;
	// fl->output_values [out_nl] = -95.0;
   // fl->output_values [out_nm] = -91.0;
   // fl->output_values [out_ns] = -80.0;
   // fl->output_values [out_nvs] = -71.0;
   // fl->output_values [out_ze] =  0.0;
   // fl->output_values [out_pvs] = 71.0;
   // fl->output_values [out_ps] = 80.0;
   // fl->output_values [out_pm] = 91.0;
   // fl->output_values [out_pl] = 95.0;
   // fl->output_values [out_pvl] = 104.0;
   // fl->output_values [out_pvvl] = 114.0;

   fl->output_values[out_nvl] = -a;
	fl->output_values[out_nl] = -b;
	fl->output_values[out_nm] = -c;
	fl->output_values[out_ns] = -d;
	fl->output_values[out_ze] = 0;
	fl->output_values[out_ps] = d;
	fl->output_values[out_pm] = c;
	fl->output_values[out_pl] = b;
	fl->output_values[out_pvl] = a;
   

   fl->rules = (rule *) malloc ((size_t)(fl->no_of_rules*sizeof(rule)));
   initFuzzyRules(fl);
   initMembershipFunctions(fl);
   return;
}

//////////////////////////////////////////////////////////////////////////////

trapezoid init_trapz (float x1,float x2,float x3,float x4, trapz_type typ) {
	
   trapezoid trz;
   trz.a = x1;
   trz.b = x2;
   trz.c = x3;
   trz.d = x4;
   trz.tp = typ;
   switch (trz.tp) {
	   
      case regular_trapezoid:
         	 trz.l_slope = 1.0/(trz.b - trz.a);
         	 trz.r_slope = 1.0/(trz.c - trz.d);
         	 break;
	 
      case left_trapezoid:
         	 trz.r_slope = 1.0/(trz.a - trz.b);
         	 trz.l_slope = 0.0;
         	 break;
	 
      case right_trapezoid:
         	 trz.l_slope = 1.0/(trz.b - trz.a);
         	 trz.r_slope = 0.0;
         	 break;
   }  /* end switch  */
   
   return trz;
}  /* end function */

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
float trapz (float x, trapezoid trz) {
   switch (trz.tp) {
	   
      case left_trapezoid:
         	 if (x <= trz.a)
         	    return 1.0;
         	 if (x >= trz.b)
         	    return 0.0;
         	 /* a < x < b */
         	 return trz.r_slope * (x - trz.b);
	 
	 
      case right_trapezoid:
         	 if (x <= trz.a)
         	    return 0.0;
         	 if (x >= trz.b)
         	    return 1.0;
         	 /* a < x < b */
         	 return trz.l_slope * (x - trz.a);
	 
      case regular_trapezoid:
         	 if ((x <= trz.a) || (x >= trz.d))
         	    return 0.0;
         	 if ((x >= trz.b) && (x <= trz.c))
         	    return 1.0;
         	 if ((x >= trz.a) && (x <= trz.b))
         	    return trz.l_slope * (x - trz.a);
         	 if ((x >= trz.c) && (x <= trz.d))
         	    return  trz.r_slope * (x - trz.d);
         	    
	 }  /* End switch  */
	 
   return 0.0;  /* should not get to this point */
}  /* End function */

//////////////////////////////////////////////////////////////////////////////
float min_of(float values[],int no_of_inps) {
   int i;
   float val;
   val = values [0];
   for (i = 1;i < no_of_inps;i++) {
       if (values[i] < val)
	  val = values [i];
   }
   return val;
}



//////////////////////////////////////////////////////////////////////////////
float fuzzy_system (float inputs[],fuzzy_system_rec fz) {
   int i,j;
   short variable_index,fuzzy_set;
   float sum1 = 0.0,sum2 = 0.0,weight;
   float m_values[MAX_NO_OF_INPUTS];
	
   
   for (i = 0;i < fz.no_of_rules;i++) {
      for (j = 0;j < fz.no_of_inputs;j++) {
         variable_index = fz.rules[i].inp_index[j];
         fuzzy_set = fz.rules[i].inp_fuzzy_set[j];
         m_values[j] = trapz(inputs[variable_index],
            fz.inp_mem_fns[variable_index][fuzzy_set]);
	   } /* end j  */
      
       weight = min_of (m_values,fz.no_of_inputs);
				
       sum1 += weight * fz.output_values[fz.rules[i].out_fuzzy_set];
       sum2 += weight;
   } /* end i  */
 
	
	if (fabs(sum2) < TOO_SMALL) {
      cout << "\r\nFLPRCS Error: Sum2 in fuzzy_system is 0.  Press key: " << endl;
      //~ getch();
      //~ exit(1);
      return 0.0;
   }
   
   return (sum1/sum2);
}  /* end fuzzy_system  */

//////////////////////////////////////////////////////////////////////////////
void free_fuzzy_rules (fuzzy_system_rec *fz) {
   if (fz->allocated){
	   free (fz->rules);
	}
	
   fz->allocated = false;
   return;
}

