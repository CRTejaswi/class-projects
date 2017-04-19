######################## IMPORT LIBRARIES #######################	 
import sl4a
import androidhelper
######################## INITIALIZATIONS ########################	 
droid1 = sl4a.Android()
droid2 = androidhelper.Android()
txt = '.txt'
########################### SAMPLE DATA #########################	
"""
qrcITEMS = QRCode(All Available Items)
qrcCART = QRCode(Cart Items)
""" 
################################################################# 
qrcITEMS = ['ITEM00','ITEM01','ITEM02','ITEM03','ITEM04']
qrcCART = []
billITEMS = [60,70,100,50,300]
billCART = []
#################################################################
##################### FUNCTION DEFINITION #######################	 
def qrcUser(countMain):
    count = countMain
    countMain = QRCUser(count)
    if countMain != -1:
        print('You have',countMain,'items in your cart')
    return countMain
def QRCUser(count):
    flag = True
    bill = 0
    qrcValue = '/storage/emulated/0/qpython/CRT13/notes/'
    print('==========================================')
    print('=========== Welcome to MegaMart ==========')
    print('==========================================')
    print('1. Add To Your Cart')
    print('2. Remove From Your Cart')
    print('3. Checkout')
    print('==========================================')
    usrInput = int(input('Please Select: '))
    while flag is True:
        if usrInput < 0 or usrInput > 3:
            print('Error! Please try again')
            flag = False
        elif usrInput == 3:
            print("You've Successfully Checked Out!")
            for i in range(0,count):
                bill += billCART[i]
            print('Your Total Bill is Rs.',bill)
            droid1.ttsSpeak('Your total bill is Rupees')
            droid1.ttsSpeak(str(bill))
            flag = False
            return -1
        else:
            scan = droid1.scanBarcode().result		
            if usrInput == 1:
                for i in range(0,5):
                    if scan['extras']['SCAN_RESULT'] == qrcITEMS[i]:                    
                        qrcCART.append(qrcITEMS[i])
                        billCART.append(billITEMS[i])
                        count +=1
                        qrcValue += str(qrcITEMS[i])
                        qrcValue += txt
                        file = open(qrcValue,'r')
                        droid1.ttsSpeak('You have successfully added')
                        for j in file:
                            droid1.ttsSpeak(j)
                        file.close()
                        qrcValue = ''
                        flag = False     
            elif usrInput == 2:
                        if count == 0:
                            print('You have no items left!')
                            flag = False
                        for i in range(0,5):
                            if scan['extras']['SCAN_RESULT'] == qrcITEMS[i]:
                                for n in range(0,count):
                                    if qrcCART[n] == qrcITEMS[i]:
                                        del qrcCART[n]
                                        del billCART[n]
                                        count -= 1
                                        qrcValue += str(qrcITEMS[i])
                                        qrcValue += txt
                                        file = open(qrcValue,'r')
                                        droid1.ttsSpeak('You have successfully removed')
                                        for j in file:
                                            droid1.ttsSpeak(j)
                                        file.close()
                                        qrcValue = ''
                                        flag = False
                                        break
    return count       
#################################################################

########################## MAIN PROGRAM #########################	 
try:
    countMain = 0
    check = True
    while check is True:
        chkinput = int(input('Enter 0 to continue...'))
        if chkinput == 0:
            count = qrcUser(countMain)
            countMain = count
        else:
            check = False 
except:
    print('Error!')           
#################################################################









