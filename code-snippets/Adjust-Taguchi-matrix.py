# Source of original Taguchi orthogonal array:
# https://www.york.ac.uk/depts/maths/tables/l18.gif
# FACTORS 	             = 8
# LEVELS FOR EACH FACTOR = 3
# TESTS 	             = 18 

g_arr_txt = '''
1,1,1,1,1,1,1,1
1,1,2,2,2,2,2,2
1,1,3,3,3,3,3,3
1,2,1,1,2,2,3,3
1,2,2,2,3,3,1,1
1,2,3,3,1,1,2,2
1,3,1,2,1,3,2,3
1,3,2,3,2,1,3,1
1,3,3,1,3,2,1,2
2,1,1,3,3,2,2,1
2,1,2,1,1,3,3,2
2,1,3,2,2,1,1,3
2,2,1,2,3,1,3,2
2,2,2,3,1,2,1,3
2,2,3,1,2,3,2,1
2,3,1,3,2,3,1,2
2,3,2,1,3,1,2,3
2,3,3,2,1,2,3,1'''


####################################################
#
# ROUTINES
#
import re

def readStringToArray( arr_txt ):
    arr_txt = re.sub( r"^\s*", "", arr_txt )
    arr_rows = re.split( r"[\r\n]", arr_txt )
    arr_org = []
    for row in arr_rows:
        cols = re.split( r",", row )
        arr_org.append( cols )
    return arr_org

def removeFactorsAndLevels( arr_org ):
    NUM_FACTORS  = 7
    ARM_V_WHEEL  = 2
    POWERTRAIN   = 4
    STEERING     = 6
    arr_new = []
    for test_num in range( len( arr_org ) ):
        new_test = []
        for factor_num in range( NUM_FACTORS ):
            level = int( arr_org[test_num][factor_num] )
            if( ( ( factor_num == ARM_V_WHEEL  ) and ( level > 2 ) ) or 
                ( ( factor_num == POWERTRAIN   ) and ( level > 2 ) ) or 
                ( ( factor_num == STEERING     ) and ( level > 2 ) ) ): 
                # Is a level we're not testing, so repeat 
                # the value from the previous test (row above)
                prev_level = arr_new[-1][factor_num]    # Re -1: worry not because the first  
                new_test.append( prev_level )           # row of arr_org doesn't fall in here
            else:
                new_test.append( str( level ) )
        arr_new.append( new_test )
    return arr_new

def isDuplicate( new_test, prev_test ):
    if( len( new_test ) != len( prev_test ) ):
        return False
    for i in range( len( new_test ) ):
        if( new_test[i] != prev_test[i] ):
            return False
    return True

def removeDuplicates( arr_new ):
    arr_final = []
    for row_i in range( len( arr_new ) ):
        b_isDuplicate = False
        for row_j in range( row_i+1, len( arr_new ) ):
            if( isDuplicate( arr_new[row_i], arr_new[row_j] ) ):
                b_isDuplicate = True;
                break
        if( not b_isDuplicate ):
            arr_final.append( arr_new[row_i] )
    return arr_final


####################################################
#
# MAIN PROCESSING
#
                              
g_arr_org = readStringToArray( g_arr_txt )

g_arr_new = removeFactorsAndLevels( g_arr_org )

g_arr_final = removeDuplicates( g_arr_new )

for row in g_arr_final:
    print( "\t".join( row ) + "\n" )

print( "Length of original 8-factor, 3-level orthogonal array:\n" + str( len( g_arr_org ) ) + "\n" )
print( "Length of new 7-factor, mixed-level orthogonal array:\n" + str( len( g_arr_final ) ) )



