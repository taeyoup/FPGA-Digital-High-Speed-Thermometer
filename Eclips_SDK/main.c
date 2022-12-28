


#include "stdio.h"
#include "xparameters.h"
#include "myPmodAD1.h"
#include "myFND.h"
#include "Xil_io.h"
#include "math.h"

#define ref_resistance 10000 // 10Korm
#define ref_volt 3.3 // 3.3Volt

void Delay(unsigned int num)
{
	volatile unsigned int i;

	for(i=0; i<num; i++);
}



int main()
{
	int j;
	volatile unsigned int data_d1;
	float Volt;
	float Resistance;
	float temperature;

	while(1){
		data_d1 = MYPMODAD1_mReadReg(XPAR_MYPMODAD1_0_S00_AXI_BASEADDR, 0 );

		Volt = 0.000806 * data_d1; // ���� ��ȯ ��

		Resistance = (Volt/ref_volt*ref_resistance) / (1-Volt/ref_volt); // ���� �й� �� -> ���� ���

		temperature = 1.0/((1.0/3435.0)*log(Resistance/(10.0*1000.0)) + (1.0/298.15)) -273.15; // ���� �µ� ��

		MYFND_mWriteReg(XPAR_MYFND_0_S00_AXI_BASEADDR,0,round(temperature)); // FND Write

		//printf("Data = %d\n", data_d1);
		//printf("Volt = %.2f KV\n", Volt);
		//printf("Resistance = %.2f Korm\n", Resistance/1000);
		printf("temperature = %.2f oC\n", temperature);
		//printf("-------------%d------------\n", j++);
		Delay(3e7);

	}


	return 0;
}
