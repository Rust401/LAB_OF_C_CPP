#ifndef PARA_H
#define PARA_H


// buoy
#define BUOY_R 1 /* m */
#define BUOY_HEIGHT 2 /* m */
#define BUOY_MASS 1000 /* kg */


// anchor
#define ANCHOR_MASS 600 /* kg */


// tube
#define TUBE_QUANTITY 4
#define TUBE_LENGTH 1 /* m */
#define TUBE_RADIUS 0.025 /* 25mm */
#define TUBE_MASS 10 /* kg */

// cylinder
#define CYLINDER_MASS 100 /* kg */
#define CYLINDER_RADIUS 0.15 /* m */
#define CYLINDER_LENGTH 1 /* M */

// chain
#define TOTAL_LENGTH 22.05 /* m */
#define UNIT_LENGTH 0.105 /* m */
#define UNIT_MASS 7 /* kg/m */
#define CHAIN_DENSITY 7800 /* kg/m3 */
#define TOTAL_COUNT (22.05/0.105)

// iron ball (hammer)
#define HAMMER_MASS 1200 /* kg */
#define HAMMER_DENSITY 7800 /* kg/m3 */


// nature
#define WIND_SPEED 36 /* m */
#define WATER_SPEED 1.5 /* m */
#define SEA_DEPTH 18 /* m */
#define SEA_WATER_DENSITY 1025 /* kg/m3 */
#define G 9.8 /* m/s2 */
#define PHI 3.1415926

// constrain
#define MAX_PHI_CYLINDER (5.0/180*PHI) /* radian */
#define MAX_PHI_LASTCHAIN (16.0/180*PHI) /* radian */

// precise level
#define DEFUALT_BIAS 0.0005 /* 0-1 */
#define DEFUALT_HAMMER_MASS_BIAS 5 /* kg */

// config
#define CHAIN_SHAPE_FILE "./chainShape.txt"



#endif //PARA_H