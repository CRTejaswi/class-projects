######################## IMPORT LIBRARIES #######################	 
import sl4a
import androidhelper
######################## INITIALIZATIONS ########################	 
droid1 = sl4a.Android()
droid2 = androidhelper.Android()
########################### SAMPLE DATA #########################	
"""
qrcSMP = QRCode(Smartphones)
qrcYTB = QRCode(Youtube Links)
""" 
################################################################# 
qrcSMP = ['SMPmice455','SMPgooPixXL','SMPonp3T','SMPhtc10','SMPsamGal6','SMPlenA7020a48','SMPlenK33A42','SMPyuYU5530','SMPlenA6020a46','SMPasuZC521TL']
qrcSMPweb = ['http://www.gsmarena.com/micromax_canvas_nitro_4g_e455-7665.php','http://www.gsmarena.com/google_pixel_xl-8345.php','http://www.gsmarena.com/oneplus_3t-8416.php','http://www.gsmarena.com/htc_10-7884.php','http://www.gsmarena.com/samsung_galaxy_s6-6849.php','http://www.gsmarena.com/lenovo_k5_note-7878.php','http://www.gsmarena.com/lenovo_k6_power-8317.php','http://www.gsmarena.com/yu_yunicorn-8002.php','http://www.gsmarena.com/lenovo_vibe_k5_plus-7947.php','http://www.gsmarena.com/asus_zenfone_3s_max_zc521tl-8550.php']

qrcYTB = ['YTBnptece01','YTBnptee01','YTBnptcse01','YTBnptme01','YTBnptce01','YTBnptase01','YTBnptche01','YTBnptphy01','YTBnptbio01','YTBnpthsc01']
qrcYTBweb = ['https://www.youtube.com/channel/UCdDLuSAR5CCBGDkgKuqPA3A','https://www.youtube.com/channel/UCTJn6buigC961hns17ELXAQ','https://www.youtube.com/channel/UCxJp9aEteKmOeobEsHXwxAw','https://www.youtube.com/channel/UCqBiwZuVP0NzSu4QR91v4jQ','https://www.youtube.com/channel/UCAVi5Zg6zSoyZUyKBtCJfmg','https://www.youtube.com/channel/UCiY8ERfD4qvD_-d-VUWh_GA','https://www.youtube.com/channel/UCqqc1GmsuANsx3s3Y0C-BsQ','https://www.youtube.com/channel/UC9vycSfjzLCR_w1C59VQo5A','https://www.youtube.com/channel/UCbWTmSK7bYM9kRZAdfy_gyg','https://www.youtube.com/channel/UCnLoshotJ_FRpzFmOChRPaQ']
#################################################################
########################### QRC Decode ##########################	 
def qrcDecode():
    flag = True
    txt = '.txt'
    qrcValue = '/storage/emulated/0/qpython/CRT13/notes/'
    print('==========================================')
    print('1. Scan QR Code')
    print('2. Add QR Code Entry')
    print('3. Delete QR Code Entry')
    print('==========================================')
    usrInput = int(input('Please Select: '))
    while flag is True:
        if usrInput < 0 or usrInput > 3:
            print('Error! Please try again')
            flag = False
        else:
            scan = droid1.scanBarcode().result
            # Scan QRCode
            if usrInput == 1:
                flag1 = True
                for i in range(0,10):
                    if scan['extras']['SCAN_RESULT'] == qrcSMP[i]:
                        qrcValue += str(qrcSMP[i])
                        qrcValue += txt
                        file = open(qrcValue,'r')
                        for j in file:
                            droid1.ttsSpeak(j)
                        file.close()
                        droid2.view(str(qrcSMPweb[i]))
                        flag1 = False
                        break
                    elif scan['extras']['SCAN_RESULT'] == qrcYTB[i]:
                        qrcValue += str(qrcYTB[i])
                        qrcValue += txt
                        file = open(qrcValue,'r')
                        for j in file:
                            droid1.ttsSpeak(j)
                        file.close()
                        droid2.view(str(qrcYTBweb[i]))
                        flag1 = False
                        break
                    else:
                        pass
                if flag1:
                    droid1.makeToast('No such entry exists!')
                    droid1.ttsSpeak('Sorry, No such entry exists.Try making a new entry!')                            
                        break
                flag = False
            # Add QRCode
            elif usrInput == 2:
                flag1 = True
                qrcStr = str(scan['extras']['SCAN_RESULT'])
                if qrcStr[0:3] == 'SMP':
                    for i in range(0,10):
                        if qrcStr == str(qrcSMP[i]):
                            droid1.makeToast('This entry already exists!')
                            droid1.ttsSpeak('This entry already exists!')                            
                            flag1 = False
                            break
                        else:
                            pass
                    if flag1:
                        qrcSMP.append(qrcStr)
                        print(qrcSMP)
                        tmp = int(input('Add info about this QR code?(1/0)'))
                        if tmp:
                            qrcNewEntry(qrcStr)
                        else:
                            pass
                        droid1.makeToast('Done!')
                        droid1.ttsSpeak('Entry Made!')
                        break
                    break
                elif qrcStr[0:3] == 'YTB':
                    for i in range(0,10):
                        if qrcStr == str(qrcYTB[i]):
                            droid1.makeToast('This entry already exists!')
                            droid1.ttsSpeak('This entry already exists!')                            
                            flag1 = False
                            break
                        else:
                            pass
                    if flag1:
                        qrcYTB.append(qrcStr)
                        print(qrcYTB)
                        tmp = int(input('Add info about this QR code?(1/0)'))
                        if tmp:
                            qrcNewEntry(qrcStr)
                        else:
                            pass
                        droid1.makeToast('Done!')
                        droid1.ttsSpeak('Entry Made!')
                        break
                    break
                flag = False
            # Delete QRCode
            elif usrInput == 3:
                flag1 = True
                qrcStr = str(scan['extras']['SCAN_RESULT'])
                if qrcStr[0:3] == 'SMP':
                    for i in range(0,10):
                        if qrcStr == str(qrcSMP[i]):
                            del qrcSMP[i]
                            droid1.makeToast('Done!')
                            droid1.ttsSpeak('Entry Deleted!')
                            flag1 = False
                            break
                        else:
                            pass
                    if flag1:
                        droid1.makeToast('Entry does not exist!')
                        droid1.ttsSpeak('Sorry, no such entry exists!')
                        break
                    break
                elif qrcStr[0:3] == 'YTB':
                    for i in range(0,10):
                        if qrcStr == str(qrcYTB[i]):
                            del qrcYTB[i]
                            droid1.makeToast('Done!')
                            droid1.ttsSpeak('Entry Deleted!')
                            flag1 = False
                            break
                        else:
                            pass
                    if flag1:
                        droid1.makeToast('Entry does not exist!')
                        droid1.ttsSpeak('Sorry, no such entry exists!')
                        break
                    break
                flag = False
            txt = ''
            qrcValue = ''
########################## QRC New Entry ########################	 
def qrcNewEntry(qrcStr):
    try:
        qrcStr += '.txt'
        file = open('/storage/emulated/0/qpython/CRT13/notes/'+qrcStr,'w')
        usrInput = input('Enter Description:')
        file.write(usrInput)
        file.close()
    except:
        print('Error!')
#################################################################
########################## MAIN PROGRAM #########################	 
try:
    check = True
    count = 1
    print('==========================================')
    print('========= Personal Info Assistant ========')
    print('==========================================')
    while check:
        qrcDecode()
        check = int(input('Continue? (1/0):'))
except:
    print('Error!')           
#################################################################



