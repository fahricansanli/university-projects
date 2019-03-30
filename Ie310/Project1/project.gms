option
    limrow = 0,
    limcol = 0,    
    solprint = off,     
    sysout = off;       


Sets
         j   customers /
$include   /Users/fahricansanli/Desktop/ders2/ie310/proje/datafiles/customers.txt
/
        t   transshipment centers /
$include   /Users/fahricansanli/Desktop/ders2/ie310/proje/datafiles/trcenters.txt
        /

        i  truck ids / 1*56 /
        
         k truck type / small,large /;

Alias (j, j1, j2);

Parameters

w(j) weight of demand of customer j /
$include   /Users/fahricansanli/Desktop/ders2/ie310/proje/datafiles/demand-weight.txt
/

v(j) volume of demand of customer j /
$include   /Users/fahricansanli/Desktop/ders2/ie310/proje/datafiles/demand-volume.txt
/

a(j1,j2) relation between customer j1 and j2 /
$include   /Users/fahricansanli/Desktop/ders2/ie310/proje/datafiles/clusterability.txt
/

u(j) unit cost of demand of customer j /
$include   /Users/fahricansanli/Desktop/ders2/ie310/proje/datafiles/trans_cost.txt
/

p(j,t) customer transshipment pairs /
$include   /Users/fahricansanli/Desktop/ders2/ie310/proje/datafiles/customer-TC.txt
/;
 
Table c(j,k) cost of transportation of customer j by using truck type k 
$include   /Users/fahricansanli/Desktop/ders2/ie310/proje/datafiles/direct-shipment-cost.txt
;

Binary Variables
d_type(j)      transportation type
truck1(i,j)    whether customer j uses small type truck i
truck2(i,j)    whether customer j uses large type truck i
truck1_used(i)    whether small truck i is used
truck2_used(i)    whether large truck i is used;


Nonnegative Variables
truck1_max(i)    max element of small truck i
truck2_max(i)    max element of large truck i
;

Variables
Z total cost;

Equations
cost                                     definition of total cost
transportation_type(j)          which tranportation type is used
customer_relation1(i,j1,j2)     make sure.......
truck1_capacity(i)                it must be less than 4
truck1_volume(i)                  capacity of small truck should not be exceeded
truck1_maximum(i,j)            maximum of truck1
truck1_usage(i)                    indicates if any small truck is used
customer_relation2(i,j1,j2)     make_sure......
truck2_capacity(i)                it must be less than 4
truck2_volume(i)                  capacity of large truck should not be exceeded
truck2_maximum(i,j)            maximum of truck2
truck2_usage(i)                    indicates if any large truck is used
;

cost..            Z =e= sum(j, (1-d_type(j))*w(j)*u(j)) + sum(i, ((sum(j, truck1(i,j)) - 1) * 125) + truck1_max(i) + (1-truck1_used(i)) * 125)
                                                                              + sum(i, ((sum(j, truck2(i,j)) - 1) * 250) + truck2_max(i) + (1-truck2_used(i)) * 250) ;
                                                                              
transportation_type(j)..        sum(i, truck1(i,j) + truck2(i,j)) =e= d_type(j);
customer_relation1(i,j1,j2).. truck1(i,j1) + truck1(i,j2) =l= a(j1,j2)+1;
truck1_capacity(i)..                sum(j, truck1(i,j)) =l= 3;
truck1_volume(i)..                 sum(j, (truck1(i,j) * v(j))) =l= 18; 
truck1_maximum(i,j)..            truck1(i,j) * c(j, "small") =l= truck1_max(i);
truck1_usage(i)..                    sum(j, truck1(i,j)) =g= truck1_used(i);
customer_relation2(i,j1,j2).. truck2(i,j1) + truck2(i,j2) =l= a(j1,j2)+1;
truck2_capacity(i)..                sum(j, truck2(i,j)) =l= 3; 
truck2_volume(i)..                 sum(j, (truck2(i,j) * v(j))) =l= 33;
truck2_maximum(i,j)..            truck2(i,j) * c(j, "large") =l= truck2_max(i);
truck2_usage(i)..                    sum(j, truck2(i,j)) =g= truck2_used(i);

Model MFW / all /;

Option MIP=XPRESS;
Option reslim=2000;
*Option heurThreads=2;

Solve MFW using MIP minimizing Z;
display d_type.L, truck1.L, truck2.L, truck1_used.L, truck2_used.L, truck1_max.L, truck2_max.L, Z.L;