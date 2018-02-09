/*
dry0097.c
ISCA tracker simulator with Raab's solution
rev0, 20jan2011pta: dry0095.c with reduced nonconcentricities
rev1, 14feb2011pta: added reference; no change to code

This program simulates an electromagnetic (EM) tracking system using three
colocated orthogonal coils for the transmitter and three colocated
orthogonal coils for the receiver.

Such tracking systems are sometimes called ISCA (Industry Standard
Coil Architecture) tracking systems, because they have long been
manufactured by various companies, and to distinguish such systems
from those that track a single-coil receiver.

Copyright (c) 2001, 2010, 2011 Peter Traneus Anderson
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

  * Neither the name of Peter Traneus Anderson nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PETER TRANEUS
ANDERSON BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Compilation command: gcc -lm dry0097.c -odry0097

First sample run:
prompt$ dry0097 20 10 1 2
dry0097.c rev0 tests Raab's position and orientation calculation.
input arguments on command line:
  NumberOfPoints = 1, 2, 20, 30, 26, or 520, others made 0.
  Verbosity =0 no print, >0 print more, <0 made 0.
  Measurement model = 1 for 9-rectangle, others made 0 for dipole.
  NumberOfRaabCalcs = 1 for once, 2 for twice, others made 2.
Number of points = 20
Verbosity = 10
SimulatedHFluxPerIModel = 1
NumberOfRaabCalcs = 2

point Perror  Oerror
num.  meters radians (...true.position.meters...) (true.orientation.quaternion)
  9  0.00187 0.08049 ( 0.05000  0.00000  0.00000) ( 1.000  0.000  0.000  0.000)
 35  0.00245 0.10694 ( 0.00000  0.05000  0.00000) ( 1.000  0.000  0.000  0.000)
 61  0.00199 0.08623 ( 0.00000  0.00000  0.05000) ( 1.000  0.000  0.000  0.000)
 87  0.00132 0.05830 ( 0.03536  0.03536  0.00000) ( 1.000  0.000  0.000  0.000)
113  0.00120 0.05319 ( 0.03536  0.00000  0.03536) ( 1.000  0.000  0.000  0.000)
139  0.00144 0.06353 ( 0.00000  0.03536  0.03536) ( 1.000  0.000  0.000  0.000)
165  0.00011 0.00036 ( 0.02887  0.02887  0.02887) ( 1.000  0.000  0.000  0.000)
191  0.00012 0.00022 (-0.02887  0.02887  0.02887) ( 1.000  0.000  0.000  0.000)
217  0.00013 0.00051 ( 0.02887 -0.02887  0.02887) ( 1.000  0.000  0.000  0.000)
243  0.00012 0.00032 ( 0.02887  0.02887 -0.02887) ( 1.000  0.000  0.000  0.000)
269  0.00097 0.00436 ( 0.50000  0.00000  0.00000) ( 1.000  0.000  0.000  0.000)
295  0.00080 0.00361 ( 0.00000  0.50000  0.00000) ( 1.000  0.000  0.000  0.000)
321  0.00087 0.00393 ( 0.00000  0.00000  0.50000) ( 1.000  0.000  0.000  0.000)
347  0.00028 0.00128 ( 0.35355  0.35355  0.00000) ( 1.000  0.000  0.000  0.000)
373  0.00000 0.00000 ( 0.35355  0.00000  0.35355) ( 1.000  0.000  0.000  0.000)
399  0.00016 0.00073 ( 0.00000  0.35355  0.35355) ( 1.000  0.000  0.000  0.000)
425  0.00001 0.00000 ( 0.28868  0.28868  0.28868) ( 1.000  0.000  0.000  0.000)
451  0.00000 0.00000 (-0.28868  0.28868  0.28868) ( 1.000  0.000  0.000  0.000)
477  0.00001 0.00000 ( 0.28868 -0.28868  0.28868) ( 1.000  0.000  0.000  0.000)
503  0.00000 0.00000 ( 0.28868  0.28868 -0.28868) ( 1.000  0.000  0.000  0.000)

Second sample run:
prompt$ dry0097 26 10 1 2
dry0097.c rev0 tests Raab's position and orientation calculation.
input arguments on command line:
  NumberOfPoints = 1, 2, 20, 30, 26, or 520, others made 0.
  Verbosity =0 no print, >0 print more, <0 made 0.
  Measurement model = 1 for 9-rectangle, others made 0 for dipole.
  NumberOfRaabCalcs = 1 for once, 2 for twice, others made 2.
Number of points = 26
Verbosity = 10
SimulatedHFluxPerIModel = 1
NumberOfRaabCalcs = 2

point Perror  Oerror
num.  meters radians (...true.position.meters...) (true.orientation.quaternion)
260  0.00011 0.00048 ( 0.50000  0.00000  0.00000) ( 0.707  0.000  0.707  0.000)
261  0.00002 0.00000 ( 0.50000  0.00000  0.00000) ( 0.924  0.000  0.383  0.000)
262  0.00003 0.00000 ( 0.50000  0.00000  0.00000) ( 0.854 -0.146  0.354  0.354)
263  0.00125 0.00542 ( 0.50000  0.00000  0.00000) ( 0.653 -0.271  0.271  0.653)
264  0.00012 0.00054 ( 0.50000  0.00000  0.00000) ( 0.354 -0.354  0.146  0.854)
265  0.00002 0.00000 ( 0.50000  0.00000  0.00000) ( 0.000 -0.383  0.000  0.924)
266  0.00001 0.00000 ( 0.50000  0.00000  0.00000) ( 0.354  0.354  0.146 -0.854)
267  0.00004 0.00000 ( 0.50000  0.00000  0.00000) ( 0.653  0.271  0.271 -0.653)
268  0.00002 0.00000 ( 0.50000  0.00000  0.00000) ( 0.854  0.146  0.354 -0.354)
269  0.00097 0.00436 ( 0.50000  0.00000  0.00000) ( 1.000  0.000  0.000  0.000)
270  0.00004 0.00000 ( 0.50000  0.00000  0.00000) ( 0.924  0.000  0.000  0.383)
271  0.00136 0.00629 ( 0.50000  0.00000  0.00000) ( 0.707  0.000  0.000  0.707)
272  0.00007 0.00031 ( 0.50000  0.00000  0.00000) ( 0.383  0.000  0.000  0.924)
273  0.00004 0.00019 ( 0.50000  0.00000  0.00000) ( 0.000  0.000  0.000  1.000)
274  0.00045 0.00204 ( 0.50000  0.00000  0.00000) ( 0.383  0.000  0.000 -0.924)
275  0.00003 0.00000 ( 0.50000  0.00000  0.00000) ( 0.707  0.000  0.000 -0.707)
276  0.00013 0.00057 ( 0.50000  0.00000  0.00000) ( 0.924  0.000  0.000 -0.383)
277  0.00002 0.00000 ( 0.50000  0.00000  0.00000) ( 0.924  0.000 -0.383  0.000)
278  0.00003 0.00000 ( 0.50000  0.00000  0.00000) ( 0.854  0.146 -0.354  0.354)
279  0.00099 0.00419 ( 0.50000  0.00000  0.00000) ( 0.653  0.271 -0.271  0.653)
280  0.00007 0.00033 ( 0.50000  0.00000  0.00000) ( 0.354  0.354 -0.146  0.854)
281  0.00002 0.00000 ( 0.50000  0.00000  0.00000) ( 0.000  0.383 -0.000  0.924)
282  0.00001 0.00000 ( 0.50000  0.00000  0.00000) ( 0.354 -0.354 -0.146 -0.854)
283  0.00002 0.00000 ( 0.50000  0.00000  0.00000) ( 0.653 -0.271 -0.271 -0.653)
284  0.00003 0.00000 ( 0.50000  0.00000  0.00000) ( 0.854 -0.146 -0.354 -0.354)
285  0.00010 0.00044 ( 0.50000  0.00000  0.00000) ( 0.707  0.000 -0.707  0.000)

Third sample run:
prompt$ dry0097 20 10 1 1
dry0097.c rev0 tests Raab's position and orientation calculation.
input arguments on command line:
  NumberOfPoints = 1, 2, 20, 30, 26, or 520, others made 0.
  Verbosity =0 no print, >0 print more, <0 made 0.
  Measurement model = 1 for 9-rectangle, others made 0 for dipole.
  NumberOfRaabCalcs = 1 for once, 2 for twice, others made 2.
Number of points = 20
Verbosity = 10
SimulatedHFluxPerIModel = 1
NumberOfRaabCalcs = 1

point Perror  Oerror
num.  meters radians (...true.position.meters...) (true.orientation.quaternion)
  9  0.00968 0.42822 ( 0.05000  0.00000  0.00000) ( 1.000  0.000  0.000  0.000)
 35  0.00942 0.41642 ( 0.00000  0.05000  0.00000) ( 1.000  0.000  0.000  0.000)
 61  0.00967 0.42738 ( 0.00000  0.00000  0.05000) ( 1.000  0.000  0.000  0.000)
 87  0.00528 0.23838 ( 0.03536  0.03536  0.00000) ( 1.000  0.000  0.000  0.000)
113  0.00483 0.21656 ( 0.03536  0.00000  0.03536) ( 1.000  0.000  0.000  0.000)
139  0.00479 0.21331 ( 0.00000  0.03536  0.03536) ( 1.000  0.000  0.000  0.000)
165  0.00023 0.00964 ( 0.02887  0.02887  0.02887) ( 1.000  0.000  0.000  0.000)
191  0.00013 0.00457 (-0.02887  0.02887  0.02887) ( 1.000  0.000  0.000  0.000)
217  0.00046 0.01253 ( 0.02887 -0.02887  0.02887) ( 1.000  0.000  0.000  0.000)
243  0.00015 0.00790 ( 0.02887  0.02887 -0.02887) ( 1.000  0.000  0.000  0.000)
269  0.00456 0.02013 ( 0.50000  0.00000  0.00000) ( 1.000  0.000  0.000  0.000)
295  0.00398 0.01785 ( 0.00000  0.50000  0.00000) ( 1.000  0.000  0.000  0.000)
321  0.00492 0.02183 ( 0.00000  0.00000  0.50000) ( 1.000  0.000  0.000  0.000)
347  0.00071 0.00321 ( 0.35355  0.35355  0.00000) ( 1.000  0.000  0.000  0.000)
373  0.00007 0.00042 ( 0.35355  0.00000  0.35355) ( 1.000  0.000  0.000  0.000)
399  0.00018 0.00080 ( 0.00000  0.35355  0.35355) ( 1.000  0.000  0.000  0.000)
425  0.00015 0.00091 ( 0.28868  0.28868  0.28868) ( 1.000  0.000  0.000  0.000)
451  0.00012 0.00046 (-0.28868  0.28868  0.28868) ( 1.000  0.000  0.000  0.000)
477  0.00034 0.00118 ( 0.28868 -0.28868  0.28868) ( 1.000  0.000  0.000  0.000)
503  0.00018 0.00084 ( 0.28868  0.28868 -0.28868) ( 1.000  0.000  0.000  0.000)

Fourth sample run:
prompt$ dry0097 26 10 1 1
dry0097.c rev0 tests Raab's position and orientation calculation.
input arguments on command line:
  NumberOfPoints = 1, 2, 20, 30, 26, or 520, others made 0.
  Verbosity =0 no print, >0 print more, <0 made 0.
  Measurement model = 1 for 9-rectangle, others made 0 for dipole.
  NumberOfRaabCalcs = 1 for once, 2 for twice, others made 2.
Number of points = 26
Verbosity = 10
SimulatedHFluxPerIModel = 1
NumberOfRaabCalcs = 1

point Perror  Oerror
num.  meters radians (...true.position.meters...) (true.orientation.quaternion)
260  0.00001 0.00023 ( 0.50000  0.00000  0.00000) ( 0.707  0.000  0.707  0.000)
261  0.00001 0.00038 ( 0.50000  0.00000  0.00000) ( 0.924  0.000  0.383  0.000)
262  0.00004 0.00018 ( 0.50000  0.00000  0.00000) ( 0.854 -0.146  0.354  0.354)
263  0.00787 0.03594 ( 0.50000  0.00000  0.00000) ( 0.653 -0.271  0.271  0.653)
264  0.00002 0.00030 ( 0.50000  0.00000  0.00000) ( 0.354 -0.354  0.146  0.854)
265  0.00007 0.00027 ( 0.50000  0.00000  0.00000) ( 0.000 -0.383  0.000  0.924)
266  0.00005 0.00013 ( 0.50000  0.00000  0.00000) ( 0.354  0.354  0.146 -0.854)
267  0.00010 0.00033 ( 0.50000  0.00000  0.00000) ( 0.653  0.271  0.271 -0.653)
268  0.00008 0.00038 ( 0.50000  0.00000  0.00000) ( 0.854  0.146  0.354 -0.354)
269  0.00456 0.02013 ( 0.50000  0.00000  0.00000) ( 1.000  0.000  0.000  0.000)
270  0.00006 0.00027 ( 0.50000  0.00000  0.00000) ( 0.924  0.000  0.000  0.383)
271  0.00787 0.03520 ( 0.50000  0.00000  0.00000) ( 0.707  0.000  0.000  0.707)
272  0.00003 0.00029 ( 0.50000  0.00000  0.00000) ( 0.383  0.000  0.000  0.924)
273  0.00002 0.00027 ( 0.50000  0.00000  0.00000) ( 0.000  0.000  0.000  1.000)
274  0.00242 0.01085 ( 0.50000  0.00000  0.00000) ( 0.383  0.000  0.000 -0.924)
275  0.00010 0.00039 ( 0.50000  0.00000  0.00000) ( 0.707  0.000  0.000 -0.707)
276  0.00004 0.00034 ( 0.50000  0.00000  0.00000) ( 0.924  0.000  0.000 -0.383)
277  0.00001 0.00034 ( 0.50000  0.00000  0.00000) ( 0.924  0.000 -0.383  0.000)
278  0.00004 0.00044 ( 0.50000  0.00000  0.00000) ( 0.854  0.146 -0.354  0.354)
279  0.00787 0.03572 ( 0.50000  0.00000  0.00000) ( 0.653  0.271 -0.271  0.653)
280  0.00002 0.00017 ( 0.50000  0.00000  0.00000) ( 0.354  0.354 -0.146  0.854)
281  0.00007 0.00020 ( 0.50000  0.00000  0.00000) ( 0.000  0.383 -0.000  0.924)
282  0.00005 0.00024 ( 0.50000  0.00000  0.00000) ( 0.354 -0.354 -0.146 -0.854)
283  0.00010 0.00041 ( 0.50000  0.00000  0.00000) ( 0.653 -0.271 -0.271 -0.653)
284  0.00008 0.00041 ( 0.50000  0.00000  0.00000) ( 0.854 -0.146 -0.354 -0.354)
285  0.00001 0.00023 ( 0.50000  0.00000  0.00000) ( 0.707  0.000 -0.707  0.000)

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* start of globals */

int Verbosity = 0; /* 0 = don't print anything

                      more positive means print more

                      negative means print errors only

                      10 = print error report as in samples above
		   */

/* ISCA coil characterization data as in dry0193.txt,
   transmitter initialized for 1-cM cubical coils as in dry0304.txt,
   receiver initialized for 1-cM cubical coils as in dry0304.txt */

double CoilCharacterizationData[6][13] = {

/* transmitter X coil data */
  {
   1.0, /* Orientation real component */
   0.0, /* Orientation i component */
   0.0, /* Orientation j component */
   0.0, /* Orientation k component */
   0.0001, /* Position X component in meters */
  -0.00005, /* Position Y component in meters */
   0.0, /* Position Z component in meters */
   0.0440, /* Effective area in square meters */
   1.0, /* Shape model = nine rectangles */
   3.0, /* Number of model-dependent parameters */
   0.0055, /* Rectangle corner Y in meters */
   0.0050, /* Rectangle corner Z in meters */
   0.00075, /* Rectangle spacing in meters */
  },
/* transmitter Y coil data */
  {
   0.5, /* Orientation real component */
   0.5, /* Orientation i component */
   0.5, /* Orientation j component */
   0.5, /* Orientation k component */
   0.0, /* Position X component in meters */
   0.0, /* Position Y component in meters */
  -0.00005, /* Position Z component in meters */
   0.0400, /* Effective area in square meters */
   1.0, /* Shape model = nine rectangles */
   3.0, /* Number of model-dependent parameters */
   0.0050, /* Rectangle corner Y in meters */
   0.0050, /* Rectangle corner Z in meters */
   0.00075, /* Rectangle spacing in meters */
  },
/* transmitter Z coil data */
  {
   0.5, /* Orientation real component */
   -0.5, /* Orientation i component */
   -0.5, /* Orientation j component */
   -0.5, /* Orientation k component */
   0.0, /* Position X component in meters */
  -0.00003, /* Position Y component in meters */
   0.00005, /* Position Z component in meters */
   0.0484, /* Effective area in square meters */
   1.0, /* Shape model = nine rectangles */
   3.0, /* Number of model-dependent parameters */
   0.0055, /* Rectangle corner Y in meters */
   0.0055, /* Rectangle corner Z in meters */
   0.00075, /* Rectangle spacing in meters */
  },
/* receiver X coil data */
  {
   1.0, /* Orientation real component */
   0.0, /* Orientation i component */
   0.0, /* Orientation j component */
   0.0, /* Orientation k component */
   0.0, /* Position X component in meters */
   0.0001, /* Position Y component in meters */
   0.0, /* Position Z component in meters */
   0.0440, /* Effective area in square meters */
   1.0, /* Shape model = nine rectangles */
   3.0, /* Number of model-dependent parameters */
   0.0055, /* Rectangle corner Y in meters */
   0.0050, /* Rectangle corner Z in meters */
   0.00075, /* Rectangle spacing in meters */
  },
/* receiver Y coil data */
  {
   0.5, /* Orientation real component */
   0.5, /* Orientation i component */
   0.5, /* Orientation j component */
   0.5, /* Orientation k component */
   0.0, /* Position X component in meters */
   0.0, /* Position Y component in meters */
  -0.00005, /* Position Z component in meters */
   0.0400, /* Effective area in square meters */
   1.0, /* Shape model = nine rectangles */
   3.0, /* Number of model-dependent parameters */
   0.0050, /* Rectangle corner Y in meters */
   0.0050, /* Rectangle corner Z in meters */
   0.00075, /* Rectangle spacing in meters */
  },
/* receiver Z coil data */
  {
   0.5, /* Orientation real component */
   -0.5, /* Orientation i component */
   -0.5, /* Orientation j component */
   -0.5, /* Orientation k component */
   0.0, /* Position X component in meters */
   0.0, /* Position Y component in meters */
   0.00004, /* Position Z component in meters */
   0.0484, /* Effective area in square meters */
   1.0, /* Shape model = nine rectangles */
   3.0, /* Number of model-dependent parameters */
   0.0055, /* Rectangle corner Y in meters */
   0.0055, /* Rectangle corner Z in meters */
   0.00075, /* Rectangle spacing in meters */
  }};

/* end of globals */

/* Difference two real 3x3 matrices */
int
MatDiff3x3(double L[3][3], double R[3][3], double D[3][3]){

  D[0][0] = L[0][0] - R[0][0];
  D[0][1] = L[0][1] - R[0][1];
  D[0][2] = L[0][2] - R[0][2];

  D[1][0] = L[1][0] - R[1][0];
  D[1][1] = L[1][1] - R[1][1];
  D[1][2] = L[1][2] - R[1][2];

  D[2][0] = L[2][0] - R[2][0];
  D[2][1] = L[2][1] - R[2][1];
  D[2][2] = L[2][2] - R[2][2];

  return 0;
}

/* Multiply two real 3x3 matrices */
int
MatMul3x3(double L[3][3], double R[3][3], double P[3][3]){

  P[0][0] = L[0][0] * R[0][0] + L[0][1] * R[1][0] + L[0][2] * R[2][0];
  P[0][1] = L[0][0] * R[0][1] + L[0][1] * R[1][1] + L[0][2] * R[2][1];
  P[0][2] = L[0][0] * R[0][2] + L[0][1] * R[1][2] + L[0][2] * R[2][2];

  P[1][0] = L[1][0] * R[0][0] + L[1][1] * R[1][0] + L[1][2] * R[2][0];
  P[1][1] = L[1][0] * R[0][1] + L[1][1] * R[1][1] + L[1][2] * R[2][1];
  P[1][2] = L[1][0] * R[0][2] + L[1][1] * R[1][2] + L[1][2] * R[2][2];

  P[2][0] = L[2][0] * R[0][0] + L[2][1] * R[1][0] + L[2][2] * R[2][0];
  P[2][1] = L[2][0] * R[0][1] + L[2][1] * R[1][1] + L[2][2] * R[2][1];
  P[2][2] = L[2][0] * R[0][2] + L[2][1] * R[1][2] + L[2][2] * R[2][2];

  return 0;
}

/*
Invert a real 3x3 matrix, using cross products and dot products,
from http://en.wikipedia.org/wiki/Matrix_inverse retrieved 17dec2010pta.
X0=X[][0], X1=X[][1], X2=X[][2] are the 3-element column vectors of X[][].
*/
int
MatInv3x3(double X[3][3], double Inv[3][3]){
  double Det = 0.0;
  double DetInv = 0.0;

  double X0CrossX1[3]= {0.0, 0.0, 0.0};
  double X1CrossX2[3]= {0.0, 0.0, 0.0};
  double X2CrossX0[3]= {0.0, 0.0, 0.0};

  X0CrossX1[0] = X[1][0] * X[2][1] - X[2][0] * X[1][1];
  X0CrossX1[1] = X[2][0] * X[0][1] - X[0][0] * X[2][1];
  X0CrossX1[2] = X[0][0] * X[1][1] - X[1][0] * X[0][1];

  X1CrossX2[0] = X[1][1] * X[2][2] - X[2][1] * X[1][2];
  X1CrossX2[1] = X[2][1] * X[0][2] - X[0][1] * X[2][2];
  X1CrossX2[2] = X[0][1] * X[1][2] - X[1][1] * X[0][2];

  X2CrossX0[0] = X[1][2] * X[2][0] - X[2][2] * X[1][0];
  X2CrossX0[1] = X[2][2] * X[0][0] - X[0][2] * X[2][0];
  X2CrossX0[2] = X[0][2] * X[1][0] - X[1][2] * X[0][0];

  /* The determinant of X is det(X) = X0.dot.(X1.cross.X2) */
  Det = X[0][0]*X1CrossX2[0] + X[1][0]*X1CrossX2[1] + X[2][0]*X1CrossX2[2];

  /* This will fill a singular matrix with NANs or INFs. */
  DetInv = 1.0 / Det;

  Inv[0][0] = DetInv * X1CrossX2[0];
  Inv[0][1] = DetInv * X1CrossX2[1];
  Inv[0][2] = DetInv * X1CrossX2[2];

  Inv[1][0] = DetInv * X2CrossX0[0];
  Inv[1][1] = DetInv * X2CrossX0[1];
  Inv[1][2] = DetInv * X2CrossX0[2];

  Inv[2][0] = DetInv * X0CrossX1[0];
  Inv[2][1] = DetInv * X0CrossX1[1];
  Inv[2][2] = DetInv * X0CrossX1[2];

  return 0;
}

/* Multiply two quaternions */
int
QuatMul(double lft[4], double rht[4], double product[4]){
  product[0] = lft[0]*rht[0] -lft[1]*rht[1] -lft[2]*rht[2] -lft[3]*rht[3];
  product[1] = lft[0]*rht[1] +lft[1]*rht[0] +lft[2]*rht[3] -lft[3]*rht[2];
  product[2] = lft[0]*rht[2] +lft[2]*rht[0] +lft[3]*rht[1] -lft[1]*rht[3];
  product[3] = lft[0]*rht[3] +lft[3]*rht[0] +lft[1]*rht[2] -lft[2]*rht[1];
  return 0;
}

/* Rotate a vector by a quaternion, giving rotated vector rv */
int
VectRot(double vector[3], double quat[4], double rv[3]){
  /* (imaginary_quaternion) converts a vector to an imaginary quaternion */
  /* (quat2vect) converts the imaginary part of a quaternion, to a vector */
  double temp[4] = {0.0, 0.0, 0.0, 0.0};
  /* temp = quat .quatmul. (imaginary_quaternion)vector */
  temp[0] = -quat[1]*vector[0] -quat[2]*vector[1] -quat[3]*vector[2];
  temp[1] = quat[0]*vector[0] +quat[2]*vector[2] -quat[3]*vector[1];
  temp[2] = quat[0]*vector[1] +quat[3]*vector[0] -quat[1]*vector[2];
  temp[3] = quat[0]*vector[2] +quat[1]*vector[1] -quat[2]*vector[0];
  /* rv = (quat2vect)(temp .quatmul. quat) */
  rv[0] = -temp[0]*quat[1] +temp[1]*quat[0] -temp[2]*quat[3] +temp[3]*quat[2];
  rv[1] = -temp[0]*quat[2] +temp[2]*quat[0] -temp[3]*quat[1] +temp[1]*quat[3];
  rv[2] = -temp[0]*quat[3] +temp[3]*quat[0] -temp[1]*quat[2] +temp[2]*quat[1];
  return 0;
}

/* Determine smallest-angle rotation quaternion which rotates 
   +X axis to direction of input vector Uvec.
   Returns 0 for success; returns -1 if input vector is too small. */
int
RotQuat(double Uvec[3], double Quaternion[4]){

  double Epsilon = 1.0e-200; /* nonzero, but 1.0-Epsilon is exactly 1.0 */
  double Xhat[3] = {1.0, 0.0, 0.0}; /* Unit vector in +X direction */
  double Umagnitude = 0.0; /* magnitude of Uvec */
  double Uhat[3] = {0.0, 0.0, 0.0}; /* unit vector in direction of Uvec */
  double G[3] = {0.0, 0.0, 0.0}; /* vector in direction of rotation axis */
  double Ghat[3] = {0.0, 0.0, 0.0}; /* unit vector in direction of G */
  double g = 0.0; /* angle of rotation about G axis */
  double h = 0.0;
  double Gmagnitude = 0.0; /* magnitude of G */
 
  /* quaternion for zero rotation */
  Quaternion[0] = 1.0;
  Quaternion[1] = 0.0;
  Quaternion[2] = 0.0;
  Quaternion[3] = 0.0;

  /* Magnitude of Uvec */
  Umagnitude = sqrt(Uvec[0]*Uvec[0] + Uvec[1]*Uvec[1] + Uvec[2]*Uvec[2]);

  if(Umagnitude < Epsilon){
    /* Uvec is too small */
    return -1;
  }

  /* unit vector in direction of Uvec */
  Uhat[0] = Uvec[0] / Umagnitude;
  Uhat[1] = Uvec[1] / Umagnitude;
  Uhat[2] = Uvec[2] / Umagnitude;

  /* Xhat .cross. Uhat = vector in direction of rotation axis */
  G[0] = Xhat[1]*Uhat[2] -Xhat[2]*Uhat[1];
  G[1] = Xhat[2]*Uhat[0] -Xhat[0]*Uhat[2];
  G[2] = Xhat[0]*Uhat[1] -Xhat[1]*Uhat[0];

  /* Xhat .dot. Uhat */
  h = Xhat[0]*Uhat[0] + Xhat[1]*Uhat[1] + Xhat[2]*Uhat[2];

  /* Magnitude of G */
  Gmagnitude = sqrt(G[0]*G[0] + G[1]*G[1] + G[2]*G[2]);

  /* rotation angle */
  g = atan2(Gmagnitude,h);

  if(Gmagnitude>Epsilon){
    /* Uhat is far enough from Xhat and -Xhat to make Ghat calculation. */
    Ghat[0] = G[0] / Gmagnitude;
    Ghat[1] = G[1] / Gmagnitude;
    Ghat[2] = G[2] / Gmagnitude;
    Quaternion[0] = cos(g/2.0);
    Quaternion[1] = sin(g/2.0) * Ghat[0];
    Quaternion[2] = sin(g/2.0) * Ghat[1];
    Quaternion[3] = sin(g/2.0) * Ghat[2];
  }

  else if(h<0){
    /* Uhat is very close to -Xhat, use pi radians rotation about +Z axis */
    Quaternion[0] = 0.0;
    Quaternion[1] = 0.0;
    Quaternion[2] = 0.0;
    Quaternion[3] = 1.0;
  }

  /* if both if()'s fail, Uhat is very close to Xhat, giving zero rotation */

  return 0;
}

/* Convert normalized quaternion to orthonormal rotation matrix
See dry0190.txt for details.
Algorithm is from pages 634 and 641 (after correcting r[2,1] error on page
641 with correct value from page 634) of:
"Closed-form solution of absolute orientation using unit quaternions",
Berthold K. P. Horn, Journal of the Optical Society of America A,
volume 4, April, 1987, pages 629-642.
*/
int
Quat2Mat(double q[4], double r[3][3]){
  r[0][0] = q[0]*q[0] + q[1]*q[1] - q[2]*q[2] - q[3] * q[3];
  r[1][1] = q[0]*q[0] - q[1]*q[1] + q[2]*q[2] - q[3] * q[3];
  r[2][2] = q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3] * q[3];
  r[0][1] = 2.0 * (q[1] * q[2] - q[0] * q[3]);
  r[1][0] = 2.0 * (q[1] * q[2] + q[0] * q[3]);
  r[0][2] = 2.0 * (q[1] * q[3] + q[0] * q[2]);
  r[2][0] = 2.0 * (q[1] * q[3] - q[0] * q[2]);
  r[1][2] = 2.0 * (q[2] * q[3] - q[0] * q[1]);
  r[2][1] = 2.0 * (q[2] * q[3] + q[0] * q[1]);
  return 0;
}

/* Convert orthonormal rotation matrix to normalized quaternion
See dry0192.txt for details.
Algorithm is from pages 641 and 642 (after correcting r[2][1] error on page
641 with correct value from page 634) of:
"Closed-form solution of absolute orientation using unit quaternions",
Berthold K. P. Horn, Journal of the Optical Society of America A,
volume 4, April, 1987, pages 629-642.
*/
int
Mat2Quat(double r[3][3], double q[4]){
  double four_q0_squared = 0.0;
  double four_q1_squared = 0.0;
  double four_q2_squared = 0.0;
  double four_q3_squared = 0.0;
  four_q0_squared = 1.0 + r[0][0] + r[1][1] + r[2][2];
  four_q1_squared = 1.0 + r[0][0] - r[1][1] - r[2][2];
  four_q2_squared = 1.0 - r[0][0] + r[1][1] - r[2][2];
  four_q3_squared = 1.0 - r[0][0] - r[1][1] + r[2][2];

  /* Choose the largest four_qX_squared, and calculate accordingly. */
  if((four_q3_squared>four_q2_squared)&&(four_q3_squared>four_q1_squared)&&
     (four_q3_squared>four_q0_squared)){
    /* four_q3_squared is largest */
    q[3] = 0.5 * sqrt(four_q3_squared);
    q[0] = (r[1][0] - r[0][1]) / (4.0 * q[3]);
    q[1] = (r[0][2] + r[2][0]) / (4.0 * q[3]);
    q[2] = (r[2][1] + r[1][2]) / (4.0 * q[3]);
  }
  else{
    /* four_q3_squared not largest */
    if((four_q2_squared>four_q1_squared)&&(four_q2_squared>four_q0_squared)){
      /* four_q2_squared is largest */
      q[2] = 0.5 * sqrt(four_q2_squared);
      q[0] = (r[0][2] - r[2][0]) / (4.0 * q[2]);
      q[1] = (r[1][0] + r[0][1]) / (4.0 * q[2]);
      q[3] = (r[2][1] + r[1][2]) / (4.0 * q[2]);
    }
    else{
      /* four_q3_squared is not largest */
      /* four_q2_squared is not largest */
      if(four_q1_squared>four_q0_squared){
        /* four_q1_squared is largest */
        q[1] = 0.5 * sqrt(four_q1_squared);
        q[0] = (r[2][1] - r[1][2]) / (4.0 * q[1]);
        q[2] = (r[1][0] + r[0][1]) / (4.0 * q[1]);
        q[3] = (r[0][2] + r[2][0]) / (4.0 * q[1]);
      }
      else{
        /* four_q0_squared is largest */
        q[0] = 0.5 * sqrt(four_q0_squared);
        q[1] = (r[2][1] - r[1][2]) / (4.0 * q[0]);
        q[2] = (r[0][2] - r[2][0]) / (4.0 * q[0]);
        q[3] = (r[1][0] - r[0][1]) / (4.0 * q[0]);
      }
    }
  }
  return 0;
}

/* Generate one of 780 points as in dry0373.txt */
int
GeneratePoint780(int PointNumber, double Position[3],
                 double Orientation[4]){

  double HugeRange = 500.0; /* meters */
  double FarRange = 0.5; /* meters */
  double NearRange = 0.05; /* meters */

  double Range = 0;
  int Point = 0;

  double SqrtHalf = sqrt(0.5);
  double SqrtThird = sqrt(1.0/3.0);

  double UnitVector[3] = {0.0, 0.0, 0.0};

  /* Latitudes and longitudes in degrees. */
  double LatLong[26][2] = {{ 90,    0},
                           { 45,    0},
                           { 45,   45},
                           { 45,   90},
                           { 45,  135},
                           { 45,  180},
                           { 45, -135},
                           { 45,  -90},
                           { 45,  -45},
                           {  0,    0},
                           {  0,   45},
                           {  0,   90},
                           {  0,  135},
                           {  0,  180},
                           {  0, -135},
                           {  0,  -90},
                           {  0,  -45},
                           {-45,    0},
                           {-45,   45},
                           {-45,   90},
                           {-45,  135},
                           {-45,  180},
                           {-45, -135},
                           {-45,  -90},
                           {-45,  -45},
                           {-90,    0}};

  double PiOver180 = atan(1.0) / 45.0;
  double LatitudeDegrees = 0.0;
  double LongitudeDegrees = 0.0;
  double LatitudeRadians = 0.0;
  double LongitudeRadians = 0.0;
  double LatitudeQuaternion[4] = {1.0, 0.0, 0.0, 0.0};
  double LongitudeQuaternion[4] = {1.0, 0.0, 0.0, 0.0};


  /* In case PointNumber is out of range */
  Position[0] = 0.0;
  Position[1] = 0.0;
  Position[2] = 0.0;
  Orientation[0] = 1.0;
  Orientation[1] = 0.0;
  Orientation[2] = 0.0;
  Orientation[3] = 0.0;

  /* Error if PointNumber out of range. */
  if(PointNumber<0){ return -1; }
  if(PointNumber>779){ return -2; }

  /* Make local copy. */
  Point = PointNumber;

  /* Set range. */
  Range = NearRange;
  if(Point>259){  
    Range = FarRange;
    Point -= 260;
  }
  if(Point>259){  
    Range = HugeRange;
    Point -= 260;
  }

  /* Now 0 <= Point < 260 */

  /* Set unit vector. */
  UnitVector[0] = 1.0;
  UnitVector[1] = 0.0;
  UnitVector[2] = 0.0;

  if(Point>25){
    UnitVector[0] = 0.0;
    UnitVector[1] = 1.0;
    UnitVector[2] = 0.0;
    Point -= 26;
  }

  if(Point>25){
    UnitVector[0] = 0.0;
    UnitVector[1] = 0.0;
    UnitVector[2] = 1.0;
    Point -= 26;
  }

  if(Point>25){
    UnitVector[0] = SqrtHalf;
    UnitVector[1] = SqrtHalf;
    UnitVector[2] = 0.0;
    Point -= 26;
  }

  if(Point>25){
    UnitVector[0] = SqrtHalf;
    UnitVector[1] = 0.0;
    UnitVector[2] = SqrtHalf;
    Point -= 26;
  }

  if(Point>25){
    UnitVector[0] = 0.0;
    UnitVector[1] = SqrtHalf;
    UnitVector[2] = SqrtHalf;
    Point -= 26;
  }

  if(Point>25){
    UnitVector[0] = SqrtThird;
    UnitVector[1] = SqrtThird;
    UnitVector[2] = SqrtThird;
    Point -= 26;
  }

  if(Point>25){
    UnitVector[0] = -SqrtThird;
    UnitVector[1] = SqrtThird;
    UnitVector[2] = SqrtThird;
    Point -= 26;
  }

  if(Point>25){
    UnitVector[0] = SqrtThird;
    UnitVector[1] = -SqrtThird;
    UnitVector[2] = SqrtThird;
    Point -= 26;
  }

  if(Point>25){
    UnitVector[0] = SqrtThird;
    UnitVector[1] = SqrtThird;
    UnitVector[2] = -SqrtThird;
    Point -= 26;
  }

  /* Calculate position. */
  Position[0] = Range * UnitVector[0];
  Position[1] = Range * UnitVector[1];
  Position[2] = Range * UnitVector[2];

  /* Now 0 <= Point <= 25 */

  /* Calculate latitude quaternion. */
  /* This is rotation around +Y axis when longitude=0, so
     LatitudeQuaternion must be right factor in QuatMul below. */
  LatitudeDegrees = LatLong[Point][0];
  LatitudeRadians = PiOver180 * LatitudeDegrees;
  LatitudeQuaternion[0] = cos(0.5*LatitudeRadians);
  LatitudeQuaternion[1] = 0.0;
  LatitudeQuaternion[2] = sin(0.5*LatitudeRadians);
  LatitudeQuaternion[3] = 0.0;

  /* Calculate longitude quaternion. */
  /* This is rotation around +Z axis for any latitude. */
  LongitudeDegrees = LatLong[Point][1];
  LongitudeRadians = PiOver180 * LongitudeDegrees;
  LongitudeQuaternion[0] = cos(0.5*LongitudeRadians);
  LongitudeQuaternion[1] = 0.0;
  LongitudeQuaternion[2] = 0.0;
  LongitudeQuaternion[3] = sin(0.5*LongitudeRadians);

  /* Calculate orientation quaternion: order of factors matters. */
  QuatMul(LongitudeQuaternion, LatitudeQuaternion, Orientation);

  if(Verbosity > 20){
    printf("LatitudeDegrees = %11.5f LongitudeDegrees = %11.5f\r\n",
           LatitudeDegrees, LongitudeDegrees);
  }

  return 0;
}

  /* Calculate field per current for one dipole coil, using variable
  names patterned after dry0321.txt equation.

  We are working in Cartesian coordinates, with no assumption about
  position or orientation of the dipole coil.

  Input quantities:
    double Aeff[3] = vector effective area of dipole coil, in square meters
    double DipolePosition[3] = position of dipole coil, in meters
    double ObserverPosition[3] = position of field observer, in meters
    double I = coil current, in amperes

  Output quantity:
    double H[3] = vector magnetic field, in amperes/meter, at field observer
  */

int
HPerIDipole(double DipolePosition[3], double Aeff[3],
            double ObserverPosition[3],
            double HPerI[3]){

  /* Quantities calculated for the dipole coil */
  double OneOverFourPi = 0.0625 / atan(1.0);
  double R[3] = {0.0, 0.0, 0.0}; /* vector from coil to observer, in meters */
  double RMagnitude = 0.0; /* magnitude of R */
  double RHat[3] = {0.0, 0.0, 0.0}; /* unit vector in R direction */
  double OneOverFourPiRCubed = 0.0;
  double ThreeRHatDotAeff = 0.0;

  /* Calculate the magnetic field H, due to dipole coil of vector
  effective area Aeff, from vectors Aeff and R */

  R[0] = ObserverPosition[0] - DipolePosition[0];
  R[1] = ObserverPosition[1] - DipolePosition[1];
  R[2] = ObserverPosition[2] - DipolePosition[2];

  RMagnitude = sqrt(R[0]*R[0] + R[1]*R[1] + R[2]*R[2]);

  RHat[0] = R[0] / RMagnitude;
  RHat[1] = R[1] / RMagnitude;
  RHat[2] = R[2] / RMagnitude;

  OneOverFourPiRCubed = OneOverFourPi / (RMagnitude * RMagnitude * RMagnitude);

  ThreeRHatDotAeff = 3.0*(RHat[0]*Aeff[0] + RHat[1]*Aeff[1] + RHat[2]*Aeff[2]);

  HPerI[0] = OneOverFourPiRCubed * (ThreeRHatDotAeff*RHat[0] - Aeff[0]);
  HPerI[1] = OneOverFourPiRCubed * (ThreeRHatDotAeff*RHat[1] - Aeff[1]);
  HPerI[2] = OneOverFourPiRCubed * (ThreeRHatDotAeff*RHat[2] - Aeff[2]);

  return 0;
}

  /* Calculate field per current for rectangle (centered on the YZ plane)
  of four straight-line current segments.

  See dry0313.txt for derivation of code from

    "Equations for the Magnetic Field Produced by One or More
    Rectangular Loops of Wire in the Same Plane", by Martin Misakian,
    Volume 105, Number 4, JulyAugust 2000, pages 557-564, Journal of
    Research of the National Institute of Standards and Technology
    [J. Res. Natl. Inst. Stand. Technol. 105, 557 (2000)], available
    online: http://www.nist.gov/jres

  We are working in Cartesian coordinates.
  The rectangle is assumed to be centered in the YZ plane.

  Input quantities:
    double CornerY = Y position of corner of rectangle, in meters
    double CornerZ = Z position of corner of rectangle, in meters
      The four corners of the rectangle are:
        (0,+CornerY,+CornerZ)
        (0,-CornerY,+CornerZ)
        (0,-CornerY,-CornerZ)
        (0,+CornerY,-CornerZ)
    double ObserverPosition[3] = position of field observer, in meters
    double I = current in amperes in rectangle

  Output quantity:
    double H[3] = magnetic field in amperes/meter, at ObserverPosition
  */

int
HPerIRectangle(double CornerY, double CornerZ, double ObserverPosition[3],
               double HPerI[3]){

  double OneOverFourPi = 0.0625 / atan(1.0);
  double SumX = 0.0;
  double SumY = 0.0;
  double SumZ = 0.0;
  double C1 = 0.0;
  double C2 = 0.0;
  double C3 = 0.0;
  double C4 = 0.0;
  double D1 = 0.0;
  double D2 = 0.0;
  double D3 = 0.0;
  double D4 = 0.0;
  double R1 = 0.0;
  double R2 = 0.0;
  double R3 = 0.0;
  double R4 = 0.0;

  /* Corner vs. ObserverPosition differences in Y direction */
  C1 = ObserverPosition[1] + CornerY;
  C2 = ObserverPosition[1] - CornerY;
  C3 = C2;
  C4 = C1;

  /* Corner vs. ObserverPosition differences in Z direction */
  D1 = ObserverPosition[2] + CornerZ;
  D2 = D1;
  D3 = ObserverPosition[2] - CornerZ;
  D4 = D3;

  R1 = sqrt(C1*C1 + D1*D1 + ObserverPosition[0]*ObserverPosition[0]);
  R2 = sqrt(C2*C2 + D2*D2 + ObserverPosition[0]*ObserverPosition[0]);
  R3 = sqrt(C3*C3 + D3*D3 + ObserverPosition[0]*ObserverPosition[0]);
  R4 = sqrt(C4*C4 + D4*D4 + ObserverPosition[0]*ObserverPosition[0]);

  SumX = 
    - (D1 / (R1*(R1+C1)) + C1 / (R1*(R1+D1)))
    + (D2 / (R2*(R2+C2)) + C2 / (R2*(R2+D2)))
    - (D3 / (R3*(R3+C3)) + C3 / (R3*(R3+D3)))
    + (D4 / (R4*(R4+C4)) + C4 / (R4*(R4+D4)));

  SumY =
    + ObserverPosition[0] / (R1*(R1+D1))
    - ObserverPosition[0] / (R2*(R2+D2))
    + ObserverPosition[0] / (R3*(R3+D3))
    - ObserverPosition[0] / (R4*(R4+D4));

  SumZ =
    + ObserverPosition[0] / (R1*(R1+C1))
    - ObserverPosition[0] / (R2*(R2+C2))
    + ObserverPosition[0] / (R3*(R3+C3))
    - ObserverPosition[0] / (R4*(R4+C4));

  HPerI[0] = OneOverFourPi * SumX;
  HPerI[1] = OneOverFourPi * SumY;
  HPerI[2] = OneOverFourPi * SumZ;

  return 0;
}

  /*
  H flux per I of two straight-line segments from Pete's Ph.D. dissertation,
  calculated using Neumann's double-integral equation.

  Meaning of H flux:  If we construct two closed circuits of
  straight-line segments, then when we apply this function to sum
  over all the segments, the sum is the H flux through circuit 2 due
  to current I flowing in circuit 1.

  Reference: Pete's Ph.D. dissertation, thesis.pdf and thesifig.pdf,
  available from http://home.comcast.net/~traneus or from the
  University of Vermont library:

  "A Source of Accurately Calculable Quasi-Static Magnetic Fields", A
  Dissertation Presented by Peter Traneus Anderson to The Faculty of the
  Graduate College of The University of Vermont In Partial Fulfillment
  of the Requirements for the Degree of Doctor of Philosophy
  Specializing in Electrical Engineering, October, 2001.

  C code modified from pages 99-111 of Pete's dissertation, using seven-point
  numerical integration to do the second integral.

  Neumann's formula for mutual inductance can be found in
  electromagnetics textbooks going back to Maxwell.  Here, instead of
  mutual inductance, Lm = mu-nought * HFluxPerI, we calculate HFluxPerI
  itself.  Unlike mutual inductance, HFluxPerI is in the same units,
  meters, as the positions of the points.

  We have two finite-length straight-line current segments, s1 and s2:

    Segment s1 has start point s1start and end point s1end.
    Segment s2 has start point s2start and end point s2end.

  Let A be a point on segment s1, and B be a point on segment s2.

  Neumann's formula as coded here, is a double line integral, with the
  first integral along segment s1, and the second integral along
  segment s2:

                                                 dA .dotproduct. dB
  HFluxPerI = OneOverFourPi INTEGRAL( INTEGRAL( -------------------- ) )
                             B on s2   A on s1         |A-B|

  where:

    dA .dotproduct. dB is the scalar dot product of vectors dA and dB.
    |A-B| is the magnitude of the distance between point A and point B.
    OneOverFourPi = 1.0 / ( 4.0 * pi )
    The outer integral moves B along s2 from s2start to s2end.
    The inner integral moves A along s1 from s1start to s1end.
    The integral of A is done analytically.
    The integral of B is done numerically.



  We are working in Cartesian coordinates, with no assumptions about
  positions or orientations of the two straight-line segments.

  Input quantities:
    double s1start[3] = start of first straight-line segment, in meters
    double s1end[3] = end of first straight-line segment, in meters
    double s2start[3] = start of second straight-line segment, in meters
    double s2end[3] = end of second straight-line segment, in meters

  Output quantity:
    double HFluxPerIThesis = scalar magnetic H flux per current, in meters
  */

double
HFluxPerIStraightLine(double s1start[3], double s1end[3], double s2start[3],
                      double s2end[3]){

  /* set numerical integration steps; 0 is minimum and is fastest */
  int Step = 0;

  double OneOverFourPi = 0.0625 / atan(1.0);
  long step_in_b_max_increment = 8; /* for seven-point rule */
  long step_in_b_max = 8;
  double Weight = 1; /* rule step weight */
  double step_in_b_max_inv;
  long step_in_b;
  double b;
  double second_integral,b_integral;
  double seg_end[3];
  double s1len[3];
  double s2len[3];
  double s1se[3];
  double sbmb[3];
  double sb[3];
  double s1len2,s2len2,sb2; /* squares of s1len, s2len, sb */
  double sbDOTs1len;
  double s1lenDOTs2len;
  double ssb2;
  double sgnarg,signe,sign_cos_theta;
  double logargnum,logargden;
  double b_integrand;
  int skip_flag = 0;
  /* define the coefficients for seven-point formula */
  double spfn,spfp,spfq;
  double spfm = ( 1867776.0/7.0 - 797568.0/3.0 )/3360.0;
  spfn = (-240.0*spfm +2752.0/15.0)/72.0;
  spfp = -16.0*spfm -9.0*spfn +64.0/3.0;
  spfq = -2.0*spfm -2.0*spfn -2.0*spfp +8.0;
  step_in_b_max = step_in_b_max_increment * (Step + 1);
  step_in_b_max_inv = 1.0 / (double)step_in_b_max;

  second_integral = 0.0;
  s1len[0] = s1end[0] - s1start[0];
  s1len[1] = s1end[1] - s1start[1];
  s1len[2] = s1end[2] - s1start[2];
  s2len[0] = s2end[0] - s2start[0];
  s2len[1] = s2end[1] - s2start[1];
  s2len[2] = s2end[2] - s2start[2];
  s1lenDOTs2len = s1len[0]*s2len[0]+s1len[1]*s2len[1]
    +s1len[2]*s2len[2];
  if(fabs(s1lenDOTs2len)>1e-200){
    s1len2 = s1len[0]*s1len[0]+s1len[1]*s1len[1]
      +s1len[2]*s1len[2];
    s2len2 = s2len[0]*s2len[0]+s2len[1]*s2len[1]
      +s2len[2]*s2len[2];
    sgnarg = (s2start[0]-s1start[0])*s1len[0]
      +(s2start[1]-s1start[1])*s1len[1]
      +(s2start[2]-s1start[2])*s1len[2];
    signe = 1.0;
    s1se[0] = s1end[0];
    s1se[1] = s1end[1];
    s1se[2] = s1end[2];
    if(sgnarg<0.0){/*sgnarg*/
      signe = -1.0;
      s1se[0] = s1start[0];
      s1se[1] = s1start[1];
      s1se[2] = s1start[2];
    }
    sbmb[0] = s2start[0] - s1se[0];
    sbmb[1] = s2start[1] - s1se[1];
    sbmb[2] = s2start[2] - s1se[2];
    b_integral = 0;
    for(step_in_b=0;step_in_b<step_in_b_max+1;step_in_b++){
      switch (step_in_b&7) {
        case 0:
          Weight = 2.0*spfm;
          if(step_in_b==0){
            Weight = spfm;
          }
          if(step_in_b==step_in_b_max){
            Weight = spfm;
          }
          skip_flag = 0;
          break;
        case 1:
          Weight = spfn;
          skip_flag = 0;
          break;
        case 2:
          Weight = 0.0;
          skip_flag = 1;
          break;
        case 3:
          Weight = spfp;
          skip_flag = 0;
          break;
        case 4:
          Weight = spfq;
          skip_flag = 0;
          break;
        case 5:
          Weight = spfp;
          skip_flag = 0;
          break;
        case 6:
          Weight = 0.0;
          skip_flag = 1;
          break;
        case 7:
          Weight = spfn;
          skip_flag = 0;
          break;
        default:
          Weight = 0.0;
          skip_flag = 1;
          break;
      }
      if(skip_flag == 0){
        b = (double)step_in_b * step_in_b_max_inv;
        sb[0] = sbmb[0] + s2len[0] * b;
        sb[1] = sbmb[1] + s2len[1] * b;
        sb[2] = sbmb[2] + s2len[2] * b;
        sb2 = sb[0]*sb[0]+sb[1]*sb[1]+sb[2]*sb[2];
        sbDOTs1len = sb[0]*s1len[0]+sb[1]*s1len[1]
         +sb[2]*s1len[2];
        sign_cos_theta = signe*sbDOTs1len/sqrt(sb2*s1len2);
        ssb2 = (s1len[0]+signe*sb[0])*(s1len[0]+signe*sb[0])
             + (s1len[1]+signe*sb[1])*(s1len[1]+signe*sb[1])
             + (s1len[2]+signe*sb[2])*(s1len[2]+signe*sb[2]);
        logargnum = sqrt(ssb2/sb2)+sqrt(s1len2/sb2)
             +sign_cos_theta;
        logargden = 1.0 + sign_cos_theta;
        b_integrand = Weight * log(logargnum/logargden);
        b_integral = b_integral + b_integrand;
      }
    }
    second_integral = b_integral*step_in_b_max_inv*s1lenDOTs2len/sqrt(s1len2);
  }
  return (OneOverFourPi * second_integral);
}

/* Calculate H flux per current in meters for
   concentric-dipole transmitter and concentric-dipole receiver,
   into 3x3 matrix

     HFluxPerIMeasured[ReceiverCoil][TransmitterCoil]

   First index is which receiver coil: 0 is X coil, 1 is Y coil, 2 is Z coil.
 Second index is which transmitter coil: 0 is X coil, 1 is Y coil, 2 is Z coil.

  Input quantities:
    global CoilCharacterizationData
    double RcvrPosition[3] = receiver position in transmitter coordinates
    double RcvrOrientation[4] = receiver orientation quaternion in transmitter
    coordinates

  Output quantity:
    double HFluxPerIMeasured = scalar magnetic  H flux per current, in meters
*/
int
HFluxPerIConcentricDipole(double RcvrPosition[3], double RcvrOrientation[4],
                          double HFluxPerIMeasured[3][3]){
  int RcvrCoilNr = 0;
  int TmtrCoilNr = 0;
  double TmtrPosition[3] = {0.0, 0.0, 0.0};
  double RcvrCoilPosition[3] = {0.0, 0.0, 0.0};
  double TmtrUnrotAeff[3] = {0.0, 0.0, 0.0};
  double RcvrUnrotAeff[3] = {0.0, 0.0, 0.0};
  double TmtrCoilOrientation[4] = {1.0, 0.0, 0.0, 0.0};
  double RcvrCoilOrientation[4] = {1.0, 0.0, 0.0, 0.0};
  double TmtrAeff[3] = {0.0, 0.0, 0.0};
  double RcvrAeff[3] = {0.0, 0.0, 0.0};
  double HPerI[3] = {0.0, 0.0, 0.0};

  /* First four elements of characterization data, are quaternion
     giving coil orientation within coil trio. */

  for(RcvrCoilNr=0;RcvrCoilNr<3;RcvrCoilNr++){
    for(TmtrCoilNr=0;TmtrCoilNr<3;
        TmtrCoilNr++){
      HFluxPerIMeasured[RcvrCoilNr][TmtrCoilNr] = 0.0;

      /* Transmitter coils are concentric, so transmitter coil
         position is same as transmitter position, and the transmitter
         is at the origin. */
      TmtrPosition[0] = 0.0;
      TmtrPosition[1] = 0.0;
      TmtrPosition[2] = 0.0;

      /* Receiver coils are concentric, so receiver coil position
         is same as receiver position. */

      /* Orientation of transmitter = (1,0,0,0), so
         transmitter coil orientation is same as in characterization data. */

      /* Calculate receiver coil orientation.
         Quaternions do not commute, so order of factors does matter. */
      QuatMul(RcvrOrientation, CoilCharacterizationData[RcvrCoilNr+3],
              RcvrCoilOrientation);

      /* Get unrotated transmitter coil effective area vector. */
      TmtrUnrotAeff[0] = CoilCharacterizationData[TmtrCoilNr][7];
      TmtrUnrotAeff[1] = 0.0;
      TmtrUnrotAeff[2] = 0.0;

      /* Rotate transmitter coil effective area vector to actual direction. */
      VectRot(TmtrUnrotAeff, CoilCharacterizationData[TmtrCoilNr],
              TmtrAeff);

      /* Calculate H at receiver dipole location */
      HPerIDipole(TmtrPosition, TmtrAeff, RcvrPosition, HPerI);

      /* Get unrotated receiver effective area vector. */
      RcvrUnrotAeff[0] = CoilCharacterizationData[RcvrCoilNr+3][7];
      RcvrUnrotAeff[1] = 0.0;
      RcvrUnrotAeff[2] = 0.0;

      /* Rotate receiver coil effective area vector to actual direction. */
      VectRot(RcvrUnrotAeff, RcvrCoilOrientation, RcvrAeff);

      /* Calculate HFluxPerI using dot product. */
      HFluxPerIMeasured[RcvrCoilNr][TmtrCoilNr] =
        HPerI[0]*RcvrAeff[0] + HPerI[1]*RcvrAeff[1] + HPerI[2]*RcvrAeff[2];
    }
  }
}

/* Calculate simulation of measured H flux per current in meters,
   into 3x3 matrix

     HFluxPerIMeasured[ReceiverCoil][TransmitterCoil]

   First index is which receiver coil: 0 is X coil, 1 is Y coil, 2 is Z coil.
 Second index is which transmitter coil: 0 is X coil, 1 is Y coil, 2 is Z coil.

  Input quantities:
    global CoilCharacterizationData
    double ShapeModel = 1 for rectangles, 0 for dipoles
    double RcvrPosition[3] = receiver position in transmitter coordinates
    double RcvrOrientation[4] = receiver orientation quaternion in transmitter
    coordinates

  Output quantity:
    double HFluxPerIMeasured = scalar magnetic  H flux per current, in meters
*/
int
SimulateHFluxPerIMeasured(int ShapeModel, double RcvrPosition[3],
                          double RcvrOrientation[4],
                          double HFluxPerIMeasured[3][3]){
  int RcvrCoilNr = 0;
  int TmtrCoilNr = 0;
  int RcvrRectangleNr = 0;
  int TmtrRectangleNr = 0;
  double TmtrCoilPosition[3] = {0.0, 0.0, 0.0};
  double RcvrCoilPosition[3] = {0.0, 0.0, 0.0};
  double RcvrUnrotCoilPosOffset[3] = {0.0, 0.0, 0.0};
  double RcvrCoilPositionOffset[3] = {0.0, 0.0, 0.0};
  double TmtrUnrotAeff[3] = {0.0, 0.0, 0.0};
  double RcvrUnrotAeff[3] = {0.0, 0.0, 0.0};
  double TmtrCoilOrientation[4] = {1.0, 0.0, 0.0, 0.0};
  double RcvrCoilOrientation[4] = {1.0, 0.0, 0.0, 0.0};
  double TmtrAeff[3] = {0.0, 0.0, 0.0};
  double RcvrAeff[3] = {0.0, 0.0, 0.0};
  int RcvrSegmentNr = 0;
  int TmtrSegmentNr = 0;

  double UnrotUntransTmtrSegmentStart[3] = {0.0, 0.0, 0.0};
  double UnrotUntransTmtrSegmentEnd[3] = {0.0, 0.0, 0.0};
  double UnrotUntransRcvrSegmentStart[3] = {0.0, 0.0, 0.0};
  double UnrotUntransRcvrSegmentEnd[3] = {0.0, 0.0, 0.0};

  double RotatedUntransTmtrSegmentStart[3] = {0.0, 0.0, 0.0};
  double RotatedUntransTmtrSegmentEnd[3] = {0.0, 0.0, 0.0};
  double RotatedUntransRcvrSegmentStart[3] = {0.0, 0.0, 0.0};
  double RotatedUntransRcvrSegmentEnd[3] = {0.0, 0.0, 0.0};

  double TmtrSegmentStart[3] = {0.0, 0.0, 0.0};
  double TmtrSegmentEnd[3] = {0.0, 0.0, 0.0};
  double RcvrSegmentStart[3] = {0.0, 0.0, 0.0};
  double RcvrSegmentEnd[3] = {0.0, 0.0, 0.0};

  double HPerI[3] = {0.0, 0.0, 0.0};

  double YStartSignTable[4] = {1.0, -1.0, -1.0, 1.0};
  double YEndSignTable[4]   = {-1.0, -1.0, 1.0, 1.0};
  double ZStartSignTable[4] = {1.0, 1.0, -1.0, -1.0};
  double ZEndSignTable[4]   = {1.0, -1.0, -1.0, 1.0};

  double TmtrAeffCorrectionFactor = 0.0;
  double RcvrAeffCorrectionFactor = 0.0;

  /* First four elements of characterization data, are quaternion
     giving coil orientation within coil trio. */

  for(RcvrCoilNr=0;RcvrCoilNr<3;RcvrCoilNr++){
    for(TmtrCoilNr=0;TmtrCoilNr<3;
        TmtrCoilNr++){
      HFluxPerIMeasured[RcvrCoilNr][TmtrCoilNr] = 0.0;

      /* Position of transmitter coil trio = (0,0,0), so
         transmitter coil position is same as in characterization data */
      TmtrCoilPosition[0] = CoilCharacterizationData[TmtrCoilNr][4];
      TmtrCoilPosition[1] = CoilCharacterizationData[TmtrCoilNr][5];
      TmtrCoilPosition[2] = CoilCharacterizationData[TmtrCoilNr][6];

      /* Orientation of transmitter coil trio = (1,0,0,0), so
         transmitter coil orientation is same as in characterization data. */

      /* Calculate receiver coil orientation.
         Quaternions do not commute, so order of factors does matter. */
      QuatMul(RcvrOrientation, CoilCharacterizationData[RcvrCoilNr+3],
              RcvrCoilOrientation);

      /* Unrotated receiver coil position offset from receiver center */
      RcvrUnrotCoilPosOffset[0] = CoilCharacterizationData[RcvrCoilNr+3][4];
      RcvrUnrotCoilPosOffset[1] = CoilCharacterizationData[RcvrCoilNr+3][5];
      RcvrUnrotCoilPosOffset[2] = CoilCharacterizationData[RcvrCoilNr+3][6];

      /* Rotate receiver coil position offset to actual direction. */
      VectRot(RcvrUnrotCoilPosOffset, RcvrCoilOrientation,
              RcvrCoilPositionOffset);

      /* Calculate receiver coil position. */
      RcvrCoilPosition[0] = RcvrPosition[0] + RcvrCoilPositionOffset[0];
      RcvrCoilPosition[1] = RcvrPosition[1] + RcvrCoilPositionOffset[1];
      RcvrCoilPosition[2] = RcvrPosition[2] + RcvrCoilPositionOffset[2];

      if(ShapeModel==1){
        /* Cubical transmitter and cubical receiver */
	for(RcvrRectangleNr=-4;RcvrRectangleNr<5;RcvrRectangleNr++){
	  for(TmtrRectangleNr=-4;TmtrRectangleNr<5;TmtrRectangleNr++){
            for(RcvrSegmentNr=0;RcvrSegmentNr<4;RcvrSegmentNr++){
              for(TmtrSegmentNr=0;TmtrSegmentNr<4;TmtrSegmentNr++){

                /* Get untranslated unrotated transmitter segment
                   start point from characterization data. */
                UnrotUntransTmtrSegmentStart[0] =
                  CoilCharacterizationData[TmtrCoilNr][12] *
                  (double)TmtrRectangleNr;
                UnrotUntransTmtrSegmentStart[1] =
                  CoilCharacterizationData[TmtrCoilNr][10] *
                  YStartSignTable[TmtrSegmentNr];
                UnrotUntransTmtrSegmentStart[2] =
                  CoilCharacterizationData[TmtrCoilNr][11] *
                  ZStartSignTable[TmtrSegmentNr];

                /* Get untranslated unrotated transmitter segment
                   end point from characterization data. */
                UnrotUntransTmtrSegmentEnd[0] =
                  CoilCharacterizationData[TmtrCoilNr][12] *
                  (double)TmtrRectangleNr;
                UnrotUntransTmtrSegmentEnd[1] =
                  CoilCharacterizationData[TmtrCoilNr][10] *
                  YEndSignTable[TmtrSegmentNr];
                UnrotUntransTmtrSegmentEnd[2] =
                  CoilCharacterizationData[TmtrCoilNr][11] *
                  ZEndSignTable[TmtrSegmentNr];

                /* Get untranslated unrotated receiver segment
                   start point from characterization data. */
                UnrotUntransRcvrSegmentStart[0] =
                  CoilCharacterizationData[RcvrCoilNr+3][12] *
                  (double)RcvrRectangleNr;
                UnrotUntransRcvrSegmentStart[1] =
                  CoilCharacterizationData[RcvrCoilNr+3][10] *
                  YStartSignTable[RcvrSegmentNr];
                UnrotUntransRcvrSegmentStart[2] =
                  CoilCharacterizationData[RcvrCoilNr+3][11] *
                  ZStartSignTable[RcvrSegmentNr];

                /* Get untranslated unrotated receiver segment
                   end point from characterization data. */
                UnrotUntransRcvrSegmentEnd[0] =
                  CoilCharacterizationData[RcvrCoilNr+3][12] *
                  (double)RcvrRectangleNr;
                UnrotUntransRcvrSegmentEnd[1] =
                  CoilCharacterizationData[RcvrCoilNr+3][10] *
                  YEndSignTable[RcvrSegmentNr];
                UnrotUntransRcvrSegmentEnd[2] =
                  CoilCharacterizationData[RcvrCoilNr+3][11] *
                  ZEndSignTable[RcvrSegmentNr];

                /* Rotate transmitter vectors to their actual orientations */
                VectRot(UnrotUntransTmtrSegmentStart,
                        CoilCharacterizationData[TmtrCoilNr],
                        RotatedUntransTmtrSegmentStart);
                VectRot(UnrotUntransTmtrSegmentEnd,
                        CoilCharacterizationData[TmtrCoilNr],
                        RotatedUntransTmtrSegmentEnd);

                /* Rotate receiver vectors to their actual orientations */
                VectRot(UnrotUntransRcvrSegmentStart,
                        RcvrCoilOrientation,
                        RotatedUntransRcvrSegmentStart);
                VectRot(UnrotUntransRcvrSegmentEnd,
                        RcvrCoilOrientation,
                        RotatedUntransRcvrSegmentEnd);

                /* Translate transmitter segment start and end points
                   to their actual positions */
                TmtrSegmentStart[0] = RotatedUntransTmtrSegmentStart[0] +
                  TmtrCoilPosition[0];
                TmtrSegmentStart[1] = RotatedUntransTmtrSegmentStart[1] +
                  TmtrCoilPosition[1];
                TmtrSegmentStart[2] = RotatedUntransTmtrSegmentStart[2] +
                  TmtrCoilPosition[2];
                TmtrSegmentEnd[0] = RotatedUntransTmtrSegmentEnd[0] +
                  TmtrCoilPosition[0];
                TmtrSegmentEnd[1] = RotatedUntransTmtrSegmentEnd[1] +
                  TmtrCoilPosition[1];
                TmtrSegmentEnd[2] = RotatedUntransTmtrSegmentEnd[2] +
                  TmtrCoilPosition[2];

                /* Translate receiver segment start and end points
                   to their actual positions */
                RcvrSegmentStart[0] = RotatedUntransRcvrSegmentStart[0] +
                  RcvrCoilPosition[0];
                RcvrSegmentStart[1] = RotatedUntransRcvrSegmentStart[1] +
                  RcvrCoilPosition[1];
                RcvrSegmentStart[2] = RotatedUntransRcvrSegmentStart[2] +
                  RcvrCoilPosition[2];
                RcvrSegmentEnd[0] = RotatedUntransRcvrSegmentEnd[0] +
                  RcvrCoilPosition[0];
                RcvrSegmentEnd[1] = RotatedUntransRcvrSegmentEnd[1] +
                  RcvrCoilPosition[1];
                RcvrSegmentEnd[2] = RotatedUntransRcvrSegmentEnd[2] +
                  RcvrCoilPosition[2];

                /* Calculate HFlux using Neumann's double integral */
                HFluxPerIMeasured[RcvrCoilNr][TmtrCoilNr] +=
                  HFluxPerIStraightLine(TmtrSegmentStart,TmtrSegmentEnd,
                                        RcvrSegmentStart,RcvrSegmentEnd);
              }
            }
          }
        }

        /* Calculate transmitter model effective area correction factor. */
        TmtrAeffCorrectionFactor = CoilCharacterizationData[TmtrCoilNr][7]/
          (CoilCharacterizationData[TmtrCoilNr][10] *
           CoilCharacterizationData[TmtrCoilNr][11] * 4.0 * 9.0);

        /* Calculate receiver model effective area correction factor. */
        RcvrAeffCorrectionFactor = CoilCharacterizationData[RcvrCoilNr+3][7]/
          (CoilCharacterizationData[RcvrCoilNr+3][10] *
           CoilCharacterizationData[RcvrCoilNr+3][11] * 4.0 * 9.0);

        /* Multiply H flux by both effective area correction factors */
        HFluxPerIMeasured[RcvrCoilNr][TmtrCoilNr] *=
          TmtrAeffCorrectionFactor * RcvrAeffCorrectionFactor;

      }
      else{
        /* Dipole transmitter and dipole receiver */

        /* Get unrotated transmitter coil effective area vector. */
        TmtrUnrotAeff[0] = CoilCharacterizationData[TmtrCoilNr][7];
        TmtrUnrotAeff[1] = 0.0;
        TmtrUnrotAeff[2] = 0.0;

        /* Rotate transmitter coil effective area vector to actual direction. */
        VectRot(TmtrUnrotAeff, CoilCharacterizationData[TmtrCoilNr],
                TmtrAeff);

        /* Calculate H at receiver dipole location */
        HPerIDipole(TmtrCoilPosition, TmtrAeff, RcvrCoilPosition, HPerI);

        /* Get unrotated receiver effective area vector. */
        RcvrUnrotAeff[0] = CoilCharacterizationData[RcvrCoilNr+3][7];
        RcvrUnrotAeff[1] = 0.0;
        RcvrUnrotAeff[2] = 0.0;

        /* Rotate receiver coil effective area vector to actual direction. */
        VectRot(RcvrUnrotAeff, RcvrCoilOrientation, RcvrAeff);

        /* Calculate HFluxPerI using dotproduct. */
        HFluxPerIMeasured[RcvrCoilNr][TmtrCoilNr] =
          HPerI[0]*RcvrAeff[0] + HPerI[1]*RcvrAeff[1] + HPerI[2]*RcvrAeff[2];
      }
    }
  }
}

/*
  Sort the magnitudes, i.e. absolute values, of three double-precision
  numbers.

  Input quantities:
    double Data[3]  contains the three quantities to magnitude-compare

  Output quantities will be 0,1,2 only:
    int Sort[3]:
      Sort[0] = 0,1,2 index of largest-magnitude Data[] element
      Sort[1] = 0,1,2 index of middle-magnitude Data[] element
      Sort[2] = 0,1,2 index of smallest-magnitude Data[] element
*/
int
SortByMagnitude3(double Data[3], int Sort[3]){

  double D0 = 0.0;
  double D1 = 0.0;
  double D2 = 0.0;

  int Largest = 0;
  int Middle = 0;
  int Smallest = 0;

  D0 = fabs(Data[0]);
  D1 = fabs(Data[1]);
  D2 = fabs(Data[2]);

  Largest = 0;
  Middle = 0;
  Smallest = 0;

  if(D0<D1){
    /* D0 is not largest, so D1 or D2 is largest */
    if(D1<D2){
      Largest = 2;
      Middle = 1;
      Smallest = 0;
    }
    else{
      Largest = 1;
      if(D0<D2){
        Middle = 2;
        Smallest = 0;
      }
      else{
        Middle = 0;
        Smallest = 2;
      }
    }
  }
  else{
    /* D1 is not largest, so D0 or D2 is largest */
    if(D0<D2){
      Largest = 2;
      Middle = 0;
      Smallest = 1;
    }
    else{
      Largest = 0;
      if(D1<D2){
        Middle = 2;
        Smallest = 1;
      }
      else{
        Middle = 1;
        Smallest = 2;
      }
    }
  }

  Sort[0] = Largest;
  Sort[1] = Middle;
  Sort[2] = Smallest;
  return 0;
}

/* Calculate receiver position and orientation using algorithm in

  "Quasi-Static Magnetic-Field Technique for Determining Position and
  Orientation", Frederick H. Raab, IEEE Transactions on Geoscience and
  Remote Sensing, Vol. GE-19, No. 4, October 1981, pages 235-243.

  See dry0195.txt, dry0196.txt, dry0231.txt .

  Input quantities:
    global CoilCharacterizationData
    double HFluxPerI[3][3] = magnetic  H flux per current, in meters

  Output quantity:
    double RcvrPosition[3] = receiver position in transmitter coordinates
    double RcvrOrientation[4] = receiver orientation quaternion in transmitter
    coordinates
*/
int
PositionAndOrientationRaab(double HFluxPerI[3][3], double RcvrPosition[3],
                           double RcvrOrientation[4]){
  double OneOverTwoPi = 0.125 / atan(1.0);
  double TwoPi = 8.0 * atan(1.0);
  int TmtrCoilNr = 0;
  double TmtrUnrotAeff[3] = {0.0, 0.0, 0.0};
  double TmtrAeffTranspose[3][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0}};
  double TmtrAeff[3][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
  double TmtrAeffInverse[3][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},
                                  {0.0, 0.0, 0.0}};
  int RcvrCoilNr = 0;
  double RcvrUnrotAeff[3] = {0.0, 0.0, 0.0};
  double RcvrAeffTranspose[3][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0}};
  double RcvrAeffTransposeInverse[3][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},
                                           {0.0, 0.0, 0.0}};
  double Temp[3][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
  double R[3][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
  double P[3] = {0.0, 0.0, 0.0}; /* squares of magnitudes of columns of R */
  double ScaledPositionSquared[3] = {0.0, 0.0, 0.0}; /* scaled squares of
    position components */
  double ScaledPositionMagnitude = 0.0;
  double ScaledPosition[3] = {0.0, 0.0, 0.0}; /* scaled position components */
  double Rho = 0.0; /* distance between transmitter and receiver, in meters */
  double RColumnDotProduct[3] = {0.0, 0.0, 0.0};
  int RColumnDotProductOrder[3] = {0, 0, 0};
  double RcvrPositionQuaternion[4] = {1.0, 0.0, 0.0, 0.0};
  double SInverse[3][3] = /* inverse of Raab's S coupling matrix */
    {{1.0, 0.0, 0.0},{0.0, -2.0, 0.0},{0.0, 0.0, -2.0}};
  double TTranspose[3][3] =
    {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
  double T[3][3] =
    {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
  double TInverse[3][3] =
    {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
  double SInverseT[3][3] =
    {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
  double TInverseSInverseT[3][3] =
    {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
  double RTInverseSInverseT[3][3] =
    {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
  double TwoPiRhoCubed = 0.0;
  double RcvrOrientationMatrix[3][3] =
    {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
  double RcvrOrientationMatrixTranspose[3][3] =
    {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};

  /* Calculate the transpose of the transmitter effective area matrix
     in square meters. */

  for(TmtrCoilNr=0;TmtrCoilNr<3;TmtrCoilNr++){
    /* Get unrotated transmitter coil effective area vector. */
    TmtrUnrotAeff[0] = CoilCharacterizationData[TmtrCoilNr][7];
    TmtrUnrotAeff[1] = 0.0;
    TmtrUnrotAeff[2] = 0.0;

    /* Rotate transmitter coil effective area vector to actual
       direction in transmitter coordinates, and save in transpose of
       transmitter effective area matrix. */
    VectRot(TmtrUnrotAeff, CoilCharacterizationData[TmtrCoilNr],
            TmtrAeffTranspose[TmtrCoilNr]);

    /* Calculate transmitter effective area matrix from its transpose. */
    TmtrAeff[0][TmtrCoilNr] = TmtrAeffTranspose[TmtrCoilNr][0];
    TmtrAeff[1][TmtrCoilNr] = TmtrAeffTranspose[TmtrCoilNr][1];
    TmtrAeff[2][TmtrCoilNr] = TmtrAeffTranspose[TmtrCoilNr][2];
  }

  /*         (XTmtrAeff[0]  YTmtrAeff[0]  ZTmtrAeff[0])
  TmtrAeff = (XTmtrAeff[1]  YTmtrAeff[1]  ZTmtrAeff[1])
             (XTmtrAeff[2]  YTmtrAeff[2]  ZTmtrAeff[2])

              units = square meters
              [first (row) index] = which component of Aeff vector
              [second (column) index] = which Aeff vector
  */

  /* Calculate the transpose of the receiver effective area matrix
     in square meters. */

  for(RcvrCoilNr=0;RcvrCoilNr<3;RcvrCoilNr++){

    /* Get unrotated receiver effective area vector. */
    RcvrUnrotAeff[0] = CoilCharacterizationData[RcvrCoilNr+3][7];
    RcvrUnrotAeff[1] = 0.0;
    RcvrUnrotAeff[2] = 0.0;

    /* Rotate receiver coil effective area vector to actual direction
       in receiver coordinates, and save in transpose of receiver
       effective area matrix. */
    VectRot(RcvrUnrotAeff, CoilCharacterizationData[RcvrCoilNr+3],
            RcvrAeffTranspose[RcvrCoilNr]);
  }

  /*                  (XRcvrAeff[0]  XRcvrAeff[1]  XRcvrAeff[2])
  RcvrAeffTranspose = (YRcvrAeff[0]  YRcvrAeff[1]  YRcvrAeff[2])
                      (ZRcvrAeff[0]  ZRcvrAeff[1]  ZRcvrAeff[2])

              units = square meters
              [first (row) index] = which Aeff vector
              [second (column) index] = which component of Aeff vector
  */

  /* Calculate the inverses.  Units are inverse square meters. */
  MatInv3x3(TmtrAeff,TmtrAeffInverse);
  MatInv3x3(RcvrAeffTranspose,RcvrAeffTransposeInverse);

  /* HFluxPerI 3x3 matrix units are meters:
   First index is which receiver coil: 0 is X coil, 1 is Y coil, 2 is Z coil.
 Second index is which transmitter coil: 0 is X coil, 1 is Y coil, 2 is Z coil.
  */

  /* Calculate Raab's measurement matrix R from measured Hflux per I.
     Units are inverse cubic meters.
   First index is which receiver coil: 0 is X coil, 1 is Y coil, 2 is Z coil.
 Second index is which transmitter coil: 0 is X coil, 1 is Y coil, 2 is Z coil.
 */
  MatMul3x3(RcvrAeffTransposeInverse,HFluxPerI,Temp);
  MatMul3x3(Temp,TmtrAeffInverse,R);

  /* TmtrCoilNr = 0,1,2 corresponds to receiver position XYZ coordinates. */
  for(TmtrCoilNr=0;TmtrCoilNr<3;TmtrCoilNr++){
  
    /* Calculate squares of the magnitudes of the columns of R, in
       inverse meters to the sixth power. */
    P[TmtrCoilNr] =
      R[0][TmtrCoilNr]*R[0][TmtrCoilNr] +
      R[1][TmtrCoilNr]*R[1][TmtrCoilNr] +
      R[2][TmtrCoilNr]*R[2][TmtrCoilNr];
  }

  /* Calculate estimates of squares of scaled position components in
       inverse meters to the sixth power. */
  ScaledPositionSquared[0] = (2.0/9.0) * (5.0*P[0]     - P[1]     - P[2]);
  ScaledPositionSquared[1] = (2.0/9.0) * (   -P[0] + 5.0*P[1]     - P[2]);
  ScaledPositionSquared[2] = (2.0/9.0) * (   -P[0]     - P[1] + 5.0*P[2]);

  /* Calculate magnitude of scaled position. */
  ScaledPositionMagnitude = sqrt(
    ScaledPositionSquared[0] +
    ScaledPositionSquared[1] +
    ScaledPositionSquared[2]);

  /* Calculated scaled position components, while replacing imaginaries
     (which can occur due to measurement errors) with zeros. */

  ScaledPosition[0] = 0.0;
  ScaledPosition[1] = 0.0;
  ScaledPosition[2] = 0.0;
  if(ScaledPositionSquared[0]>0.0){
    ScaledPosition[0] = sqrt(ScaledPositionSquared[0]);
  }
  if(ScaledPositionSquared[1]>0.0){
    ScaledPosition[1] = sqrt(ScaledPositionSquared[1]);
  }
  if(ScaledPositionSquared[2]>0.0){
    ScaledPosition[2] = sqrt(ScaledPositionSquared[2]);
  }

  /* Calculate distance between transmitter and receiver, Rho, in meters */
  Rho = pow(OneOverTwoPi/ScaledPositionMagnitude, 1.0/3.0);

  /* Calculate estimated unsigned position from R. */
  RcvrPosition[0] = ScaledPosition[0]*Rho/ScaledPositionMagnitude;
  RcvrPosition[1] = ScaledPosition[1]*Rho/ScaledPositionMagnitude;
  RcvrPosition[2] = ScaledPosition[2]*Rho/ScaledPositionMagnitude;

  /* Calculate dot products of columns of R:
     RColumnDotProduct[2] = dot product between R[][0] and R[][1]
     RColumnDotProduct[0] = dot product between R[][1] and R[][2]
     RColumnDotProduct[1] = dot product between R[][2] and R[][0] */
  RColumnDotProduct[2] = R[0][0]*R[0][1] + R[1][0]*R[1][1] + R[2][0]*R[2][1];
  RColumnDotProduct[0] = R[0][1]*R[0][2] + R[1][1]*R[1][2] + R[2][1]*R[2][2];
  RColumnDotProduct[1] = R[0][2]*R[0][0] + R[1][2]*R[1][0] + R[2][2]*R[2][0];

  /* Find the largest-magnitude and second-largest-magnitude dot products */
  SortByMagnitude3(RColumnDotProduct, RColumnDotProductOrder);

  /* We now determine the signs of two of the position components from
  the signs of the dot products, based on Table II on page 238 of
  Raab's paper referenced above.  The sign of the third position
  component cannot be determined here, due to the hemisphere ambiguity.

  At this point, RcvrPosition[] components are all positive.
  Test signs of largest-magnitude and middle-magnitude dot products:
    If both are positive, no position signs are changed. 
    If one is negative, change the position sign pointed to by the other one.
    If both are negative, change the position sign pointed to by neither.

  Measurement errors can give an incorrect sign for a small dot product.

  Positions far from axes and far from planes containing axes, make
  all three dot products large, so the sign determination is reliable.

  Positions close to the plane containing two axes, have one large and
  two small dot products.  The one large dot product reliably
  determines the same-or-different condition of the signs of the two
  large position components.  A sign error on the small position
  component, causes only a small position error.

  Positions close to an axis, make all three dot products small, so
  the position signs are unreliable.  This does not matter, for a
  close-to-axis position has only one large position component.
  Sign errors on the two small position components, cause only
  small position errors.
  */
  if(RColumnDotProduct[RColumnDotProductOrder[0]]<0){
    /* Largest-magnitude dot product is negative */
    if(RColumnDotProduct[RColumnDotProductOrder[1]]<0){
      /* Both are negative; change sign pointed to by smallest */
      RcvrPosition[RColumnDotProductOrder[2]] *= -1.0;
    }
    else{
      /* Only largest is negative; change sign pointed to by middle */
      RcvrPosition[RColumnDotProductOrder[1]] *= -1.0;
    }
  }
  else if(RColumnDotProduct[RColumnDotProductOrder[1]]<0){
    /* Only second-largest is negative; change sign pointed to by largest */
    RcvrPosition[RColumnDotProductOrder[0]] *= -1.0;
  }

  /* Next, we calculate estimated orientation from R and estimated position. */

  /* Calculate quaternion to rotate +X axis to direction of RcvrPosition */
  RotQuat(RcvrPosition, RcvrPositionQuaternion);

  /* Calculate matrix T to rotate +X axis to direction of RcvrPosition */
  Quat2Mat(RcvrPositionQuaternion, TInverse);
  MatInv3x3(TInverse, T);

  /* Calculate matrix products */
  MatMul3x3(SInverse, T, SInverseT);
  MatMul3x3(TInverse, SInverseT, TInverseSInverseT);
  MatMul3x3(R, TInverseSInverseT, RTInverseSInverseT);

  /* Calculate receiver orientation matrix. */
  TwoPiRhoCubed = TwoPi * Rho * Rho * Rho;
  RcvrOrientationMatrix[0][0] = TwoPiRhoCubed * RTInverseSInverseT[0][0];
  RcvrOrientationMatrix[0][1] = TwoPiRhoCubed * RTInverseSInverseT[0][1];
  RcvrOrientationMatrix[0][2] = TwoPiRhoCubed * RTInverseSInverseT[0][2];
  RcvrOrientationMatrix[1][0] = TwoPiRhoCubed * RTInverseSInverseT[1][0];
  RcvrOrientationMatrix[1][1] = TwoPiRhoCubed * RTInverseSInverseT[1][1];
  RcvrOrientationMatrix[1][2] = TwoPiRhoCubed * RTInverseSInverseT[1][2];
  RcvrOrientationMatrix[2][0] = TwoPiRhoCubed * RTInverseSInverseT[2][0];
  RcvrOrientationMatrix[2][1] = TwoPiRhoCubed * RTInverseSInverseT[2][1];
  RcvrOrientationMatrix[2][2] = TwoPiRhoCubed * RTInverseSInverseT[2][2];

  /* Calculate receiver orientation quaternion */
  Mat2Quat(RcvrOrientationMatrix, RcvrOrientation);
  RcvrOrientation[1] *= -1.0;
  RcvrOrientation[2] *= -1.0;
  RcvrOrientation[3] *= -1.0;

  return 0;
}

int
main(int argc, char *argv[]){

  /*
  Our simple ISCA tracker has one transmitter coil trio and one receiver
  coil trio, so has a hemisphere ambiguity:  Multiplying the position
  vector by -1, has no effect on the signals induced in the receiver coils.

  I choose to use the (1,1,1) hemisphere:

    if((position .dot. (1,1,1))<0){
      position = position * -1.0;
    }

  This means that the +X, +Y, and +Z axes are all within the hemisphere,
  so behavior near the axes can be explored without hemisphere problems.
  */
  int CorrectNumberOfCommandLineArguments = 5;
  double Hemisphere[3] = {1.0, 1.0, 1.0};
  int SimulatedHFluxPerIModel = 0; /* 1 cubical-cubical, otherwise dipoles */
  int NumberOfRaabCalcs = 0; /* 1 = one, otherwise two */
  int NotDone = 0;
  int PointNumber = 0;
  int NumberOfPoints = 0;
  double TruePosition[3] = {0.0, 0.0, 0.0};
  double TrueOrientation[4] = {1.0, 0.0, 0.0, 0.0};
  double TrueOrientationComplement[4] = {1.0, 0.0, 0.0, 0.0};
  double ZeroPosition[3] = {0.0, 0.0, 0.0}; /* to be left unchanged */
  double ZeroOrientation[4] = {1.0, 0.0, 0.0, 0.0}; /* to be left unchanged */
  double FirstPositionEstimate[3] = {0.0, 0.0, 0.0};
  double FirstOrientationEstimate[4] = {1.0, 0.0, 0.0, 0.0};
  double FirstOrientationEstimateError[4] = {1.0, 0.0, 0.0, 0.0};
  double SecondPositionEstimate[3] = {0.0, 0.0, 0.0};
  double SecondOrientationEstimate[4] = {1.0, 0.0, 0.0, 0.0};
  double SecondOrientationEstimateError[4] = {1.0, 0.0, 0.0, 0.0};
  double PositionErrorMagnitude = 0.0; /* meters */
  double OrientationErrorMagnitude = 0.0; /* radians */
  double HFluxPerIMeasured[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0}
  }; /* meters; HFluxPerIMeasured[receiver][transmitter] */
  double HFluxPerIEstimatedDetailed[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0}
  }; /* meters */
  double HFluxPerIEstimatedConcentricDipole[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0}
  }; /* meters */
  double HFluxPerIEstimatedCorrection[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0}
  }; /* meters */
  double HFluxPerICorrected[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0}
  }; /* meters */

  if(argc!=CorrectNumberOfCommandLineArguments){
    printf("Wrong number of command-line arguments.\r\n");
   }

  if(argc==CorrectNumberOfCommandLineArguments){
    Verbosity = atoi(argv[2]);
    if(Verbosity<0){ Verbosity = 0; }
  }

  if((argc!=CorrectNumberOfCommandLineArguments)||(Verbosity>0)){
    printf("dry0097.c rev1 tests Raab's position and orientation calculation.\r\n");
    printf("input arguments on command line:\r\n");
    printf("  NumberOfPoints = 1, 2, 20, 30, 26, or 520, others made 0.\r\n");
    printf("  Verbosity =0 no print, >0 print more, <0 made 0.\r\n");
    printf("  Measurement model = 1 for 9-rectangle, others made 0 for dipole.\r\n"); 
    printf("  NumberOfRaabCalcs = 1 for once, 2 for twice, others made 2.\r\n");
  }

  if(argc!=CorrectNumberOfCommandLineArguments){
    return -1029;
  }

  NumberOfPoints = atoi(argv[1]);
  switch (NumberOfPoints){
    case 1:
    case 2:
    case 20:
    case 30:
    case 26:
    case 520:
      break;
    default:
      NumberOfPoints = 0;
      break;
  }

  /* Verbosity = atoi(argv[2]); coded just above */

  SimulatedHFluxPerIModel = atoi(argv[3]);
  if(SimulatedHFluxPerIModel != 1){
     SimulatedHFluxPerIModel = 0;
  }

  NumberOfRaabCalcs = atoi(argv[4]);
  if(NumberOfRaabCalcs != 1){
    NumberOfRaabCalcs = 2;
  }

  if(Verbosity>0){
    printf("Number of points = %i\r\n",NumberOfPoints);
    printf("Verbosity = %i\r\n",Verbosity);
    printf("SimulatedHFluxPerIModel = %i\r\n",SimulatedHFluxPerIModel);
    printf("NumberOfRaabCalcs = %i\r\n",NumberOfRaabCalcs);
  }

  if(Verbosity==10){
    printf("\r\n");
    printf("point Perror  Oerror\r\n");
    printf("num.  meters radians (...true.position.meters...) (true.orientation.quaternion)\r\n");
  }

  NotDone = 1;

  switch (NumberOfPoints){
    case 1:
      PointNumber = 269;
      break;
    case 2:
      PointNumber = 9 - 260;
      break;
    case 20:
    case 30:
      PointNumber = 9 - 26;
      break;
    case 26:
      PointNumber = 260 - 1;
      break;
    case 520:
      PointNumber = 0 - 1;
      break;
    default:
      PointNumber = -1;
      NotDone = 0;
      break;
  }

  while(NotDone){

    switch (NumberOfPoints){
      case 1:
        NotDone = 0;
        break;
      case 2:
        PointNumber = PointNumber + 260;
        if(PointNumber>259){
           NotDone = 0;
        }
        break;
      case 20:
        PointNumber = PointNumber + 26;
        if(PointNumber>477){
           NotDone = 0;
        }
        break;
      case 30:
        PointNumber = PointNumber + 26;
        if(PointNumber>737){
           NotDone = 0;
        }
        break;
      case 26:
        PointNumber++;
        if(PointNumber>284){
           NotDone = 0;
        }
        break;
      case 520:
        PointNumber++;
        if(PointNumber>518){
           NotDone = 0;
        }
        break;
      default:
        PointNumber = 0;
        NotDone = 0;
        break;
    }

    /* Simulate true position vector and orientation quaternion. */
    GeneratePoint780(PointNumber, TruePosition, TrueOrientation);

    /* Calculate complement of true orientation, for later error calcs. */
    TrueOrientationComplement[0] = TrueOrientation [0];
    TrueOrientationComplement[1] = -TrueOrientation[1];
    TrueOrientationComplement[2] = -TrueOrientation[2];
    TrueOrientationComplement[3] = -TrueOrientation[3];

    if(Verbosity>10){
      if(PointNumber < 520){
        printf("%3i  P=(%8.5f %8.5f %8.5f)  O=(%8.5f %8.5f %8.5f %8.5f)\r\n",
               PointNumber, TruePosition[0],
               TruePosition[1], TruePosition[2],
               TrueOrientation[0], TrueOrientation[1],
               TrueOrientation[2], TrueOrientation[3]);
      }
      else{
        printf("%3i  P=(%8.3f %8.3f %8.3f)  O=(%8.5f %8.5f %8.5f %8.5f)\r\n",
               PointNumber, TruePosition[0],
               TruePosition[1], TruePosition[2],
               TrueOrientation[0], TrueOrientation[1],
               TrueOrientation[2], TrueOrientation[3]);
      }
    }

    /* Coil characterization data is hard-coded for now. */

    /* Calculate simulated Hflux per I measurements */
    SimulateHFluxPerIMeasured(SimulatedHFluxPerIModel, TruePosition,
                              TrueOrientation, HFluxPerIMeasured);

    /* Future expansion:
         Calculate simulated ADC data. Later substitute real ADC data.
         Calculate Hflux per I from ADC data.
    */

    /* Calculate first estimate of position and orientation */
    PositionAndOrientationRaab(HFluxPerIMeasured, FirstPositionEstimate,
                               FirstOrientationEstimate);

    /* Correct position hemisphere. */
    if(Hemisphere[0]*FirstPositionEstimate[0]+
       Hemisphere[1]*FirstPositionEstimate[1]+
       Hemisphere[2]*FirstPositionEstimate[2]<0){
      FirstPositionEstimate[0] *= -1.0;
      FirstPositionEstimate[1] *= -1.0;
      FirstPositionEstimate[2] *= -1.0;
    }

    /* Calculate error in first orientation estimate. */
    QuatMul(FirstOrientationEstimate,TrueOrientationComplement,
            FirstOrientationEstimateError);

    /* Calculate position error magnitude in meters */
    PositionErrorMagnitude = sqrt(
      (FirstPositionEstimate[0]-TruePosition[0])*
      (FirstPositionEstimate[0]-TruePosition[0])+
      (FirstPositionEstimate[1]-TruePosition[1])*
      (FirstPositionEstimate[1]-TruePosition[1])+
      (FirstPositionEstimate[2]-TruePosition[2])*
      (FirstPositionEstimate[2]-TruePosition[2]));

    /* Calculate orientation error magnitude in radians */
    OrientationErrorMagnitude = 2.0 * sqrt(
      FirstOrientationEstimateError[1]*
      FirstOrientationEstimateError[1]+
      FirstOrientationEstimateError[2]*
      FirstOrientationEstimateError[2]+
      FirstOrientationEstimateError[3]*
      FirstOrientationEstimateError[3]);

    if(Verbosity>13){
      if(PointNumber < 520){
        printf("1est P=(%8.5f %8.5f %8.5f)  O=(%8.5f %8.5f %8.5f %8.5f)\r\n",
               FirstPositionEstimate[0],
               FirstPositionEstimate[1], FirstPositionEstimate[2],
               FirstOrientationEstimate[0], FirstOrientationEstimate[1],
               FirstOrientationEstimate[2], FirstOrientationEstimate[3]);
      }
      else{
        printf("1est P=(%8.3f %8.3f %8.3f)  O=(%8.5f %8.5f %8.5f %8.5f)\r\n",
               FirstPositionEstimate[0],
               FirstPositionEstimate[1], FirstPositionEstimate[2],
               FirstOrientationEstimate[0], FirstOrientationEstimate[1],
               FirstOrientationEstimate[2], FirstOrientationEstimate[3]);
      }
      printf("Oerror=(%8.5f %8.5f %8.5f %8.5f)\r\n",
             FirstOrientationEstimateError[0], FirstOrientationEstimateError[1],
             FirstOrientationEstimateError[2],
             FirstOrientationEstimateError[3]);
    }

    if(NumberOfRaabCalcs != 1){

      /* See Herb Jones U.S. patent 5,307,072, "Non-concentricity
         compensation in position and orientation measurement systems",
         for earlier and more restricted example of correction process.
         I believe this patent expires July 9, 2012. */

      /* Calculate estimated Hflux per I from estimated position and orientation
         using nonconcentric detailed coil model. */
      SimulateHFluxPerIMeasured(SimulatedHFluxPerIModel, FirstPositionEstimate,
                                FirstOrientationEstimate,
                                HFluxPerIEstimatedDetailed);

      /* Calculate estimated Hflux per I from estimated position and orientation
         using concentric dipole coil model. */
      HFluxPerIConcentricDipole(FirstPositionEstimate, FirstOrientationEstimate,
                                HFluxPerIEstimatedConcentricDipole);

      /* Calculate correction = (detailed-dipole) difference of above two. */
      MatDiff3x3(HFluxPerIEstimatedDetailed, HFluxPerIEstimatedConcentricDipole,
                 HFluxPerIEstimatedCorrection);

      /* Calculate Hflux per I corrected by subtracting correction.
         HFluxPerICorrected */
      MatDiff3x3(HFluxPerIMeasured, HFluxPerIEstimatedCorrection,
                 HFluxPerICorrected);

      if(Verbosity>16){
        printf("HFluxPerIMeasured[rcvr][tmtr]\r\n");
        printf("               (%15.7e %15.7e %15.7e)\r\n",
               HFluxPerIMeasured[0][0],HFluxPerIMeasured[0][1],
               HFluxPerIMeasured[0][2]);
        printf("             = (%15.7e %15.7e %15.7e)\r\n",
               HFluxPerIMeasured[1][0],HFluxPerIMeasured[1][1],
               HFluxPerIMeasured[1][2]);
        printf("               (%15.7e %15.7e %15.7e) meters\r\n",
               HFluxPerIMeasured[2][0],HFluxPerIMeasured[2][1],
               HFluxPerIMeasured[2][2]);
      }

      if(Verbosity>17){
        printf("HFluxPerIEstimatedDetailed\r\n");
        printf("               (%15.7e %15.7e %15.7e)\r\n",
               HFluxPerIEstimatedDetailed[0][0],
               HFluxPerIEstimatedDetailed[0][1],
               HFluxPerIEstimatedDetailed[0][2]);
        printf("             = (%15.7e %15.7e %15.7e)\r\n",
               HFluxPerIEstimatedDetailed[1][0],
               HFluxPerIEstimatedDetailed[1][1],
               HFluxPerIEstimatedDetailed[1][2]);
        printf("               (%15.7e %15.7e %15.7e) meters\r\n",
               HFluxPerIEstimatedDetailed[2][0],
               HFluxPerIEstimatedDetailed[2][1],
               HFluxPerIEstimatedDetailed[2][2]);
      }

      if(Verbosity>18){
        printf("HFluxPerIEstimatedConcentricDipole\r\n");
        printf("               (%15.7e %15.7e %15.7e)\r\n",
               HFluxPerIEstimatedConcentricDipole[0][0],
               HFluxPerIEstimatedConcentricDipole[0][1],
               HFluxPerIEstimatedConcentricDipole[0][2]);
        printf("             = (%15.7e %15.7e %15.7e)\r\n",
               HFluxPerIEstimatedConcentricDipole[1][0],
               HFluxPerIEstimatedConcentricDipole[1][1],
               HFluxPerIEstimatedConcentricDipole[1][2]);
        printf("               (%15.7e %15.7e %15.7e) meters\r\n",
               HFluxPerIEstimatedConcentricDipole[2][0],
               HFluxPerIEstimatedConcentricDipole[2][1],
               HFluxPerIEstimatedConcentricDipole[2][2]);
     }

      if(Verbosity>19){
        printf("HFluxPerIEstimatedCorrection\r\n");
        printf("               (%15.7e %15.7e %15.7e)\r\n",
               HFluxPerIEstimatedCorrection[0][0],
               HFluxPerIEstimatedCorrection[0][1],
               HFluxPerIEstimatedCorrection[0][2]);
        printf("             = (%15.7e %15.7e %15.7e)\r\n",
               HFluxPerIEstimatedCorrection[1][0],
               HFluxPerIEstimatedCorrection[1][1],
               HFluxPerIEstimatedCorrection[1][2]);
        printf("               (%15.7e %15.7e %15.7e) meters\r\n",
               HFluxPerIEstimatedCorrection[2][0],
               HFluxPerIEstimatedCorrection[2][1],
               HFluxPerIEstimatedCorrection[2][2]);
      }

      if(Verbosity>20){
        printf("HFluxPerICorrected\r\n");
        printf("               (%15.7e %15.7e %15.7e)\r\n",
               HFluxPerICorrected[0][0],HFluxPerICorrected[0][1],
               HFluxPerICorrected[0][2]);
        printf("             = (%15.7e %15.7e %15.7e)\r\n",
               HFluxPerICorrected[1][0],HFluxPerICorrected[1][1],
               HFluxPerICorrected[1][2]);
        printf("               (%15.7e %15.7e %15.7e) meters\r\n",
               HFluxPerICorrected[2][0],HFluxPerICorrected[2][1],
               HFluxPerICorrected[2][2]);
      }

        /* Calculate second estimate of position and orientation */
        PositionAndOrientationRaab(HFluxPerICorrected, SecondPositionEstimate,
                                   SecondOrientationEstimate);

        /* Correct position hemisphere. */
        if(Hemisphere[0]*SecondPositionEstimate[0]+
           Hemisphere[1]*SecondPositionEstimate[1]+
           Hemisphere[2]*SecondPositionEstimate[2]<0){
          SecondPositionEstimate[0] *= -1.0;
          SecondPositionEstimate[1] *= -1.0;
          SecondPositionEstimate[2] *= -1.0;
        }

        /* Calculate error in second orientation estimate. */
        QuatMul(SecondOrientationEstimate,TrueOrientationComplement,
                SecondOrientationEstimateError);

        if(Verbosity>12){
          if(PointNumber < 520){
            printf("2est P=(%8.5f %8.5f %8.5f)  O=(%8.5f %8.5f %8.5f %8.5f)\r\n",
                   SecondPositionEstimate[0],
                   SecondPositionEstimate[1], SecondPositionEstimate[2],
                   SecondOrientationEstimate[0], SecondOrientationEstimate[1],
                   SecondOrientationEstimate[2], SecondOrientationEstimate[3]);
        }
        else{
          printf("2est P=(%8.3f %8.3f %8.3f)  O=(%8.5f %8.5f %8.5f %8.5f)\r\n",
                 SecondPositionEstimate[0],
                 SecondPositionEstimate[1], SecondPositionEstimate[2],
                 SecondOrientationEstimate[0], SecondOrientationEstimate[1],
                 SecondOrientationEstimate[2], SecondOrientationEstimate[3]);
        }
        printf("Oerror=(%8.5f %8.5f %8.5f %8.5f)\r\n",
               SecondOrientationEstimateError[0],
               SecondOrientationEstimateError[1],
               SecondOrientationEstimateError[2],
               SecondOrientationEstimateError[3]);

      }

    /* Calculate position error magnitude in meters */
    PositionErrorMagnitude = sqrt(
      (SecondPositionEstimate[0]-TruePosition[0])*
      (SecondPositionEstimate[0]-TruePosition[0])+
      (SecondPositionEstimate[1]-TruePosition[1])*
      (SecondPositionEstimate[1]-TruePosition[1])+
      (SecondPositionEstimate[2]-TruePosition[2])*
      (SecondPositionEstimate[2]-TruePosition[2]));

    /* Calculate orientation error magnitude in radians */
    OrientationErrorMagnitude = 2.0 * sqrt(
      SecondOrientationEstimateError[1]*
      SecondOrientationEstimateError[1]+
      SecondOrientationEstimateError[2]*
      SecondOrientationEstimateError[2]+
      SecondOrientationEstimateError[3]*
      SecondOrientationEstimateError[3]);

    }

    if(Verbosity==10){
      if(PointNumber < 520){
        printf("%3i %8.5f %7.5f (%8.5f %8.5f %8.5f) (%6.3f %6.3f %6.3f %6.3f)\r\n",
               PointNumber, PositionErrorMagnitude,
               OrientationErrorMagnitude,
               TruePosition[0],
               TruePosition[1], TruePosition[2],
               TrueOrientation[0], TrueOrientation[1],
               TrueOrientation[2], TrueOrientation[3]);
      }
      else{
        printf("%3i %8.5f %7.5f (%8.3f %8.3f %8.3f) (%6.3f %6.3f %6.3f %6.3f)\r\n",
               PointNumber, PositionErrorMagnitude,
               OrientationErrorMagnitude,
               TruePosition[0],
               TruePosition[1], TruePosition[2],
               TrueOrientation[0], TrueOrientation[1],
               TrueOrientation[2], TrueOrientation[3]);
      }
    }

  } /* Matches while(done) */
}
