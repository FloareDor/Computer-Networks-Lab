
import random 

def generate_test_cases(l):
	frame_nos = []
	data = []
	waiting_time = []
	acknowledgement = []
	resends = []
	for ind in range(l):
		frame_nos.append(ind+1)

		x = random.randrange(10,100)
		data.append(x)

		wt = random.randrange(0,9)
		#print(wt)
		wt_s = ""
		if wt == 0:
			wt_s = "0"
		elif wt == 1:
			wt_s = "1"
		elif wt == 2:
			wt_s = "1,2"
		else:
			for i in range(1,wt+1):
				wt_s += str(i)
				if i != wt:
					wt_s+=","
		
		waiting_time.append(wt_s)

		#flags = ["Yes", "No"]
		ack = "Yes"
		if wt > 2:
			ack = "No"
		acknowledgement.append(ack)

		resend = "No"
		if ack == "No":
			resend = "Resend"
		resends.append(resend)

		if ack == "No":
			#print(i)
			frame_nos.append(ind+1)
			#frame_nos.append(i-1)
			data.append(x)
			waiting_time.append("0")
			acknowledgement.append("Yes")
			resends.append("No")
			ind+=1

	return frame_nos, data, waiting_time, acknowledgement, resends

def print_data(frame_nos, data, waiting_times, acknowledgements, resends):
    # Print header
    print("Frame_No\tData\tWaiting_Time (Sec)\tAcknowledgement\tResend")
    
    # Iterate over the lists and print the data for each row
    for i in range(len(frame_nos)):
        print(f"{frame_nos[i]}\t\t{data[i]}\t\t{waiting_times[i]}\t\t{acknowledgements[i]}\t\t{resends[i]}")


if __name__ == "__main__":
	l = int(input("Enter the number of frames to be transmitted: "))
	
	frame_nos, data, waiting_time, acknowledgement, resend = generate_test_cases(l)

	print_data(frame_nos, data, waiting_time, acknowledgement, resend)


	



	
		
	
		
		
		
	