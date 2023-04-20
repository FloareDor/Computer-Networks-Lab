#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	int data[n];
	int stuffedData[n+(n/5)+1];

	for(int i = 0; i<n; i++){
		scanf("%d", &data[i]);
		//printf("%d ", data[i]);
	}
	int count = 0;
	int stuffedCount = 0;
	for(int i = 0; i < n; i++){
		if (data[i] == 1){
			count+=1;
		}
		if(count == 5){
			stuffedData[stuffedCount] = 1;
			stuffedData[stuffedCount+1] = 0;
			stuffedCount+=2;
			count = 0;
		}
		else{
		stuffedData[stuffedCount] = data[i];
		stuffedCount+=1;
		}

		if (data[i] == 0){
			count = 0;
		}
	}

	for(int i = 0; i < stuffedCount; i++){
		printf("%d", stuffedData[i]);
	}

    return 0;
}
