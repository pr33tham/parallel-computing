ARCHITECTURE MESH2(25);
#include <stdlib.h>
#include <math.h>
#define number_of_processes 150
#define number_of_points 70
float process_list[number_of_processes];
float stream global_sum_value[number_of_processes];

float start, end, h, my_sum, final_output;
int p, num, r;


float f(float l)
	{
		return( sqrt(4 - l*l) );
	}


void Integration_Func(int my_index, float start, float end, float h)
	{
		float local_sum = 0;

		float l;

		int num;

		l = start + my_index*(end-start)/ number_of_processes;

		for (num = 1; num <= number_of_points; num++)

		{
			local_sum = local_sum + f(l);
			l = l + h;
		}
			local_sum = h * local_sum;
			send(global_sum_value[my_index],local_Sum);
	 }

main()
	{
				start = 0;

				end = 2;

				int local_Sum = 0;

				h = (end - start)/(number_of_processes * number_of_points);
				forall p = 0 to number_of_processes -1 do

					Integration_Func(p, start, end, h);

				for(r=0; r< number_of_processes; r++)

				{
							recv(global_sum_value[r],process_list[r]);
				}

				for(p=0; p< number_of_processes; p++)

						{
							my_sum = my_sum + process_list[p];
						}

				cout.precision(10);

				final_output = my_sum + h/2*(f(end)-f(start));

				cout << "Integral of f(x) from a to b :" << final_output;

	}
