import os
import sys
import smtplib
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

def SendMail(ImgFileName, toMail):

    with open(ImgFileName, 'rb') as f:
        img_data = f.read()

    msg = MIMEMultipart()
    msg['Subject'] = 'Your picture - PHOTOMIXER'
    msg['From'] = 'm2k21ivs@gmail.com'
    msg['To'] = str(toMail)

    text = MIMEText("test")
    msg.attach(text)
    image = MIMEImage(img_data, name=os.path.basename(ImgFileName))
    msg.attach(image)

    s = smtplib.SMTP(host='smtp.gmail.com', port=587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login('m2k21ivs@gmail.com', 'maabada123')
    s.sendmail('m2k21ivs@gmail.com', str(toMail), msg.as_string())
    s.quit()

    print("ok")
	
# none imagePath toMail 
# images/b.jpg
#shellygoman123@gmail.com
def main():
	
    SendMail(sys.argv[1], sys.argv[2])
	
if __name__ == "__main__":
    main()

