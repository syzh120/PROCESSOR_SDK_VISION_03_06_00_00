/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 *
 * \ingroup EXAMPLES_API
 * \defgroup EXAMPLES_VIDEO_SENSOR_API APIs for controlling external sensors
 *
 *         Sensor APIs can be used to control external sensors.
 *         Drivers for sensors can be part of BSP or any other package.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file video_sensor.h
 *
 * \brief APIs for controlling external sensors.
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef ISS_TABLES_IPIPE_GAMMA_BT709_H_
#define ISS_TABLES_IPIPE_GAMMA_BT709_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define ISS_TABLE_IPIPE_GAMMA_BT709                     \
{                                                       \
0,   9,                                                 \
9,   9,                                                 \
18,   9,                                                \
27,   9,                                                \
36,   9,                                                \
45,   9,                                                \
54,   9,                                                \
63,   9,                                                \
72,   9,                                                \
81,   9,                                                \
90,   8,                                                \
98,   8,                                                \
106,   8,                                               \
114,   7,                                               \
121,   7,                                               \
128,   7,                                               \
135,   7,                                               \
142,   6,                                               \
148,   6,                                               \
154,   6,                                               \
160,   6,                                               \
166,   6,                                               \
172,   5,                                               \
177,   6,                                               \
183,   5,                                               \
188,   5,                                               \
193,   5,                                               \
198,   5,                                               \
203,   5,                                               \
208,   5,                                               \
213,   4,                                               \
217,   5,                                               \
222,   4,                                               \
226,   5,                                               \
231,   4,                                               \
235,   4,                                               \
239,   5,                                               \
244,   4,                                               \
248,   4,                                               \
252,   4,                                               \
256,   4,                                               \
260,   4,                                               \
264,   4,                                               \
268,   4,                                               \
272,   3,                                               \
275,   4,                                               \
279,   4,                                               \
283,   3,                                               \
286,   4,                                               \
290,   4,                                               \
294,   3,                                               \
297,   4,                                               \
301,   3,                                               \
304,   4,                                               \
308,   3,                                               \
311,   3,                                               \
314,   4,                                               \
318,   3,                                               \
321,   3,                                               \
324,   3,                                               \
327,   4,                                               \
331,   3,                                               \
334,   3,                                               \
337,   3,                                               \
340,   3,                                               \
343,   3,                                               \
346,   3,                                               \
349,   3,                                               \
352,   3,                                               \
355,   3,                                               \
358,   3,                                               \
361,   3,                                               \
364,   3,                                               \
367,   3,                                               \
370,   3,                                               \
373,   3,                                               \
376,   2,                                               \
378,   3,                                               \
381,   3,                                               \
384,   3,                                               \
387,   2,                                               \
389,   3,                                               \
392,   3,                                               \
395,   3,                                               \
398,   2,                                               \
400,   3,                                               \
403,   3,                                               \
406,   2,                                               \
408,   3,                                               \
411,   2,                                               \
413,   3,                                               \
416,   2,                                               \
418,   3,                                               \
421,   2,                                               \
423,   3,                                               \
426,   2,                                               \
428,   3,                                               \
431,   2,                                               \
433,   3,                                               \
436,   2,                                               \
438,   3,                                               \
441,   2,                                               \
443,   3,                                               \
446,   2,                                               \
448,   2,                                               \
450,   3,                                               \
453,   2,                                               \
455,   2,                                               \
457,   3,                                               \
460,   2,                                               \
462,   2,                                               \
464,   3,                                               \
467,   2,                                               \
469,   2,                                               \
471,   2,                                               \
473,   3,                                               \
476,   2,                                               \
478,   2,                                               \
480,   2,                                               \
482,   2,                                               \
484,   3,                                               \
487,   2,                                               \
489,   2,                                               \
491,   2,                                               \
493,   2,                                               \
495,   2,                                               \
497,   3,                                               \
500,   2,                                               \
502,   2,                                               \
504,   2,                                               \
506,   2,                                               \
508,   2,                                               \
510,   2,                                               \
512,   2,                                               \
514,   2,                                               \
516,   2,                                               \
518,   2,                                               \
520,   2,                                               \
522,   2,                                               \
524,   3,                                               \
527,   2,                                               \
529,   2,                                               \
531,   2,                                               \
533,   2,                                               \
535,   2,                                               \
537,   1,                                               \
538,   2,                                               \
540,   2,                                               \
542,   2,                                               \
544,   2,                                               \
546,   2,                                               \
548,   2,                                               \
550,   2,                                               \
552,   2,                                               \
554,   2,                                               \
556,   2,                                               \
558,   2,                                               \
560,   2,                                               \
562,   2,                                               \
564,   1,                                               \
565,   2,                                               \
567,   2,                                               \
569,   2,                                               \
571,   2,                                               \
573,   2,                                               \
575,   2,                                               \
577,   1,                                               \
578,   2,                                               \
580,   2,                                               \
582,   2,                                               \
584,   2,                                               \
586,   1,                                               \
587,   2,                                               \
589,   2,                                               \
591,   2,                                               \
593,   2,                                               \
595,   1,                                               \
596,   2,                                               \
598,   2,                                               \
600,   2,                                               \
602,   1,                                               \
603,   2,                                               \
605,   2,                                               \
607,   2,                                               \
609,   1,                                               \
610,   2,                                               \
612,   2,                                               \
614,   2,                                               \
616,   1,                                               \
617,   2,                                               \
619,   2,                                               \
621,   1,                                               \
622,   2,                                               \
624,   2,                                               \
626,   1,                                               \
627,   2,                                               \
629,   2,                                               \
631,   2,                                               \
633,   1,                                               \
634,   2,                                               \
636,   1,                                               \
637,   2,                                               \
639,   2,                                               \
641,   1,                                               \
642,   2,                                               \
644,   2,                                               \
646,   1,                                               \
647,   2,                                               \
649,   2,                                               \
651,   1,                                               \
652,   2,                                               \
654,   1,                                               \
655,   2,                                               \
657,   2,                                               \
659,   1,                                               \
660,   2,                                               \
662,   1,                                               \
663,   2,                                               \
665,   2,                                               \
667,   1,                                               \
668,   2,                                               \
670,   1,                                               \
671,   2,                                               \
673,   1,                                               \
674,   2,                                               \
676,   2,                                               \
678,   1,                                               \
679,   2,                                               \
681,   1,                                               \
682,   2,                                               \
684,   1,                                               \
685,   2,                                               \
687,   1,                                               \
688,   2,                                               \
690,   1,                                               \
691,   2,                                               \
693,   1,                                               \
694,   2,                                               \
696,   1,                                               \
697,   2,                                               \
699,   1,                                               \
700,   2,                                               \
702,   1,                                               \
703,   2,                                               \
705,   1,                                               \
706,   2,                                               \
708,   1,                                               \
709,   2,                                               \
711,   1,                                               \
712,   2,                                               \
714,   1,                                               \
715,   2,                                               \
717,   1,                                               \
718,   2,                                               \
720,   1,                                               \
721,   1,                                               \
722,   2,                                               \
724,   1,                                               \
725,   2,                                               \
727,   1,                                               \
728,   2,                                               \
730,   1,                                               \
731,   2,                                               \
733,   1,                                               \
734,   1,                                               \
735,   2,                                               \
737,   1,                                               \
738,   2,                                               \
740,   1,                                               \
741,   1,                                               \
742,   2,                                               \
744,   1,                                               \
745,   2,                                               \
747,   1,                                               \
748,   1,                                               \
749,   2,                                               \
751,   1,                                               \
752,   2,                                               \
754,   1,                                               \
755,   1,                                               \
756,   2,                                               \
758,   1,                                               \
759,   1,                                               \
760,   2,                                               \
762,   1,                                               \
763,   2,                                               \
765,   1,                                               \
766,   1,                                               \
767,   2,                                               \
769,   1,                                               \
770,   1,                                               \
771,   2,                                               \
773,   1,                                               \
774,   1,                                               \
775,   2,                                               \
777,   1,                                               \
778,   1,                                               \
779,   2,                                               \
781,   1,                                               \
782,   1,                                               \
783,   2,                                               \
785,   1,                                               \
786,   1,                                               \
787,   2,                                               \
789,   1,                                               \
790,   1,                                               \
791,   2,                                               \
793,   1,                                               \
794,   1,                                               \
795,   2,                                               \
797,   1,                                               \
798,   1,                                               \
799,   1,                                               \
800,   2,                                               \
802,   1,                                               \
803,   1,                                               \
804,   2,                                               \
806,   1,                                               \
807,   1,                                               \
808,   1,                                               \
809,   2,                                               \
811,   1,                                               \
812,   1,                                               \
813,   2,                                               \
815,   1,                                               \
816,   1,                                               \
817,   1,                                               \
818,   2,                                               \
820,   1,                                               \
821,   1,                                               \
822,   1,                                               \
823,   2,                                               \
825,   1,                                               \
826,   1,                                               \
827,   1,                                               \
828,   2,                                               \
830,   1,                                               \
831,   1,                                               \
832,   1,                                               \
833,   2,                                               \
835,   1,                                               \
836,   1,                                               \
837,   1,                                               \
838,   2,                                               \
840,   1,                                               \
841,   1,                                               \
842,   1,                                               \
843,   2,                                               \
845,   1,                                               \
846,   1,                                               \
847,   1,                                               \
848,   1,                                               \
849,   2,                                               \
851,   1,                                               \
852,   1,                                               \
853,   1,                                               \
854,   1,                                               \
855,   2,                                               \
857,   1,                                               \
858,   1,                                               \
859,   1,                                               \
860,   1,                                               \
861,   2,                                               \
863,   1,                                               \
864,   1,                                               \
865,   1,                                               \
866,   1,                                               \
867,   2,                                               \
869,   1,                                               \
870,   1,                                               \
871,   1,                                               \
872,   1,                                               \
873,   2,                                               \
875,   1,                                               \
876,   1,                                               \
877,   1,                                               \
878,   1,                                               \
879,   1,                                               \
880,   2,                                               \
882,   1,                                               \
883,   1,                                               \
884,   1,                                               \
885,   1,                                               \
886,   1,                                               \
887,   2,                                               \
889,   1,                                               \
890,   1,                                               \
891,   1,                                               \
892,   1,                                               \
893,   1,                                               \
894,   1,                                               \
895,   2,                                               \
897,   1,                                               \
898,   1,                                               \
899,   1,                                               \
900,   1,                                               \
901,   1,                                               \
902,   1,                                               \
903,   2,                                               \
905,   1,                                               \
906,   1,                                               \
907,   1,                                               \
908,   1,                                               \
909,   1,                                               \
910,   1,                                               \
911,   1,                                               \
912,   2,                                               \
914,   1,                                               \
915,   1,                                               \
916,   1,                                               \
917,   1,                                               \
918,   1,                                               \
919,   1,                                               \
920,   1,                                               \
921,   2,                                               \
923,   1,                                               \
924,   1,                                               \
925,   1,                                               \
926,   1,                                               \
927,   1,                                               \
928,   1,                                               \
929,   1,                                               \
930,   1,                                               \
931,   1,                                               \
932,   2,                                               \
934,   1,                                               \
935,   1,                                               \
936,   1,                                               \
937,   1,                                               \
938,   1,                                               \
939,   1,                                               \
940,   1,                                               \
941,   1,                                               \
942,   1,                                               \
943,   1,                                               \
944,   1,                                               \
945,   2,                                               \
947,   1,                                               \
948,   1,                                               \
949,   1,                                               \
950,   1,                                               \
951,   1,                                               \
952,   1,                                               \
953,   1,                                               \
954,   1,                                               \
955,   1,                                               \
956,   1,                                               \
957,   1,                                               \
958,   1,                                               \
959,   1,                                               \
960,   2,                                               \
962,   1,                                               \
963,   1,                                               \
964,   1,                                               \
965,   1,                                               \
966,   1,                                               \
967,   1,                                               \
968,   1,                                               \
969,   1,                                               \
970,   1,                                               \
971,   1,                                               \
972,   1,                                               \
973,   1,                                               \
974,   1,                                               \
975,   1,                                               \
976,   1,                                               \
977,   1,                                               \
978,   1,                                               \
979,   1,                                               \
980,   1,                                               \
981,   2,                                               \
983,   1,                                               \
984,   1,                                               \
985,   1,                                               \
986,   1,                                               \
987,   1,                                               \
988,   1,                                               \
989,   1,                                               \
990,   1,                                               \
991,   1,                                               \
992,   1,                                               \
993,   1,                                               \
994,   1,                                               \
995,   1,                                               \
996,   1,                                               \
997,   1,                                               \
998,   1,                                               \
999,   1,                                               \
1000,   1,                                              \
1001,   1,                                              \
1002,   1,                                              \
1003,   1,                                              \
1004,   1,                                              \
1005,   1,                                              \
1006,   1,                                              \
1007,   1,                                              \
1008,   1,                                              \
1009,   1,                                              \
1010,   1,                                              \
1011,   1,                                              \
1012,   1,                                              \
1013,   1,                                              \
1014,   1,                                              \
1015,   1,                                              \
1016,   1,                                              \
1017,   1,                                              \
1018,   1,                                              \
1019,   1,                                              \
1020,   1,                                              \
1021,   1,                                              \
1022,   1,                                              \
1023,   1                                               \
}

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
