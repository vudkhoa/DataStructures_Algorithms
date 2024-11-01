# QUAN LY CHUYEN BAY
## Table of Contents
- [ĐỀ BÀI](#1)
- [HƯỚNG DẪN CÀI ĐẶT](#2)
- [HƯỚNG DẪN SỬ DỤNG](#23)
- [CÁC TÍNH NĂNG NỔI BẬC TRONG ĐỒ ÁN](#24)
## ĐỀ BÀI <a name="1"></a>
### Máy bay (Airplane)
#### - Mảng con trỏ tối đa 300 máy bay
#### - Mỗi máy bay có các thông tin: Số hiệu MB(C15), loại máy bay(C40), số dãy, số dòng
#### - Mỗi máy bay có 1 số hiệu duy nhất
#### - Số chỗ = số dãy * số dòng (số chỗ >= 20)
### Chuyến bay (Flight) 
#### - Danh sách liên kết đơn (Mã CB(C15), Ngày giờ khởi hành, sân bay đến, trạng thái, Số hiệu MB, danh sách vé) 
#### - Mỗi chuyến bay có 1 mã duy nhất
#### - Trạng thái chuyến bay bao gồm: 0 --> hủy chuyến, 1 --> còn vé, 2 --> hết vé, 3 --> hoàn tất
#### - Danh sách vé cho biết thông tin vé trên chuyến bay, và số CMND của hành khách đã đặt vé đó
#### - Danh sách vé được cấp phát bộ nhớ tự động dựa vào số chỗ của máy bay thực hiện chuyến bay
#### - Danh sách chuyến bay luôn có sẵn thứ tự theo mã chuyến bay
### Hành khách (Passenger)
#### Cây nhị phân tìm kiếm cân bằng(Số CMND , Ho, Ten,  Phai)
### Chương trình có các chức năng sau
#### a/ Cập nhập danh sách các máy bay (thêm / xóa / hiệu chỉnh)
#### b/ Cập nhật chuyến bay: cho phép lập chuyến bay mới, hiệu chỉnh ngày giờ khởi hành của chuyến bay, sân bay đến, số hiệu máy bay, hủy chuyến.
#### c/ Đặt vé: cho phép đặt vé trên 1 chuyến bay; nếu thông tin hành khách chưa có thì tự động cập nhật vào danh sách hành khách, nếu có rồi thì in ra màn hình để kiểm tra. Mỗi vé đều phải ghi nhận số CMND của hành khách; nếu hành khách chưa có số CMND thì yêu cầu nhập thông tin hành khách trước. Trên 1 chuyến bay, mỗi hành khách chỉ được mua 1 vé.
#### d/ Hủy vé: cho phép hủy vé đã đặt của hành khách.
e/ In danh sách các hành khách thuộc 1 chuyến bay dựa vào mã chuyến bay. Kết xuất:¬¬¬¬
DANH SÁCH HÀNH KHÁCH THUỘC CHUYẾN BAY ######
Ngày giờ khởi hành: dd/mm/yyyy hh:mm.  Nơi đến : xxxxxxxxxxx

	STT  	SỐ VÉ  	SỐ CMND  	HỌ TÊN  	PHÁI
#### f/ In danh sách các chuyến bay khởi hành trong  ngày dd/mm/yyyy đến nơi XXXX   (cho biết cụ thể số lượng các vé còn trống và giờ khởi hành)
#### g/ In danh sách các vé còn trống của 1 chuyến bay có mã chuyến bay là X. 
#### h/ Thống kê số lượt thực hiện chuyến bay của từng máy bay theo thứ tự  số lượt thực hiện giảm dần. Kết xuất: 
	Số hiệu máy bay		Số lượt thực hiện chuyến bay
### Lưu ý: Chương trình cho phép lưu các danh sách vào file; Kiểm tra các điều kiện khi nhập liệu làm dữ liệu bị sai.

## HƯỚNG DẪN CÀI ĐẶT <a name="2"></a>
https://wide-lunch-878.notion.site/Setup-v-c-i-t-337a59ce1ea1450d9560c0fd434d79e0?pvs=4
## HƯỚNG DẪN SỬ DỤNG <a name="23"></a>
### LOGIN: Trang đăng nhập <a name="3"></a>
![z5566111907141_cf6a4eb4b19737c6f0cfe04445f3d425](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/dbbe929c-50e7-43a5-8e3c-acf79cfe1187)
#### - Đăng nhập vào ứng dụng, nhấn login
----------------------------------------------------------------------------------------------------------------------------------------
### PASSENGER: Trang giao diện hành khách. <a name="4"></a>
![z5566111941960_26f8a0333d40996179c7dc1cee76baa6](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/f4a7eff3-10f2-45a6-89ba-76f95c96b23c)
#### - Hiển thị danh sách chuyến bay, lựa chọn 1 chuyến bay để xem danh sách hành khách trên chuyến bay đó. Trên mỗi phần tử chuyến bay chưa thông tin về:
|MÃ SỐ CHUYẾN BAY|THỜI GIAN KHỞI HÀNH - Ngày Tháng Năm Giờ Phút Địa điểm tới|
|-|-|
#### - Khung "FILLTER" lọc các chuyến bay theo thời gian và địa điểm.
#### - Tính năng [ALL PASSENGER](#5) cho phép dẫn đến trang xem toàn bộ hành khách đã từng đặt vé máy bay.
#### - Tính năng "RESET ALL" cho phép đặt tất cả ô tìm kiếm và khung lọc về mặc định.
#### - Thanh tìm kiếm theo mã chuyến bay. (SPECIAL) - [KMP Algorithm](#21)
#### - Đồng hồ cập nhật theo thời gian thực - [Time Date](#22)
#### - LogOut giúp thoát ứng dụng trở lại trang [LOGIN](#3)
----------------------------------------------------------------------------------------------------------------------------------------
### ALL PASSENGER: Trang hiển thị tất cả thông tin các hành khách đã từng đặt vé máy bay. <a name="5"></a>
![z5566111941925_50b7a127d2fa708051e31665ea799ef7](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/97946691-205d-4d16-a18c-4eb00ad0c9b6)
#### - Mỗi hành khách gồm các thông tin
|Mã căn cước công dân|Họ và tên|Giới tính|
|-|-|-|
#### - Các chức năng sắp xếp danh sách hành khách theo:
|Mã căn cước|Họ|Tên|Giới tính|
|-|-|-|-|
#### - Khung "INFOMATION" hiển thị chi tiết thông tin cũng như tiện cho việc sửa và thêm hành khách
#### - Thanh tìm kiếm hành khách theo Mã căn cước - [KMP Algorithm](#21)
#### - Tính năng chỉnh sửa thông tin hành khách - [EDIT PASSENGER](#6).
#### - Tính năng thêm hành khách - [ADD PASSENGER](#7)
#### - Back cho phép quay lại trang chính của - [PASSENGER](#4)
----------------------------------------------------------------------------------------------------------------------------------------
### EDIT PASSENGER: Chỉnh sửa thông tin hành khách <a name="6"></a>
![z5566111941951_8b69fe26d1098deb5cba6f1ab0137ab9](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/2df57ee0-d5b8-48e6-bcca-86499a69c7f2)
#### - Tính năng cho phép chính sửa lại:
|Căn cước|Họ tên|Giới tính|
|-|-|-|
#### 
#### - Điều kiện:
|Không bỏ trống bất kì thông tin nào|Đảm bảo không trùng lặp CCCD|
|-|-|
----------------------------------------------------------------------------------------------------------------------------------------
### ADD PASSENGER: Cho phép nhập thêm thông tin hành khách, đảm bảo đầy đủ thông tin và không trùng lặp. <a name="7"></a>
![z5566111941966_92cabdb383aa95f09ae038699773dbd2](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/f36fc183-3b13-419e-9367-529e39a4565c)
----------------------------------------------------------------------------------------------------------------------------------------
### FLIGHT: Trang chính thể hiện các chuyến bay. <a name="8"></a>
![z5566111976819_714ed5ea0f7a9bc0a93554cbfbb90308](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/e56d724b-52a9-456c-bc42-d2dd9f6a4388)
#### - Thanh tìm kiếm theo mã chuyến bay - [KMP Algorithm](#21)
#### - Mỗi phần tử sẽ thể hiện 1 chuyến bay nhất định: 
|Thông tin| 
|---------|
|Mã chuyến bay|
|Ngày giờ khởi hành|
|Điểm đến|
|Mã máy bay thực hiện chuyến bay|
|Trạng thái chuyến bay|
|Số lượng vé đã đặt/tổng số vé|
#### - Tính năng cập nhật chuyến bay theo thời gian thực - [Time Date](#22)
#### - Sắp xếp danh sách chuyến bay theo
|Mã chuyến bay|Thời gian thực hiện chuyến bay (từ tương lai trở về quá khứ)|
|-|-|
#### - Tính năng [FILTER BY TIME PERIOD](#9) lọc danh sách chuyến bay giữa 2 khoảng thời gian xác định. 
#### - Khung "CONTROL" thực hiện các chức năng điều khiển cho phép lọc các chuyến bay theo thời gian và địa điểm đến.
#### - Tính năng đặt vé máy bay - [BOOK](#14)
|||
|-|-|
|[EDIT FLIGHT](#10)|Tính năng cho phép chỉnh sửa thông tin chuyến bay|
|[ADD FLIGHT](#11)|Tính năng cho phép khởi tạo chuyến bay|
|Điều kiện|Đảm bảo Mã chuyến bay không trùng lặp và không cho phép khởi tạo thời gian chuyến bay trong quá khứ|  
#### - Tính năng cho phép hủy 1 chuyến bay (được chọn) - CANCEL FLIGHT
----------------------------------------------------------------------------------------------------------------------------------------
### FILTER BY TIME PERIOD: Lọc chuyến bay trong 2 khoảng thời gian <a name="9"></a>
![z5566111976848_97a1ebe16ac3c506135ad429e85a8e59](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/975197a3-a296-4095-a16b-c76da6fd4b1d)
#### - Yêu cầu nhập đầy đủ ngày tháng năm.
----------------------------------------------------------------------------------------------------------------------------------------
### EIDT FLIGHT: Chỉnh sửa thông tin cho 1 chuyến bay <a name="10"></a>
![z5566112012919_a08c78631bb58aeadd93bca2cf7438e6](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/4354f133-cd59-48a5-9450-dffc5059bfc8)
#### - Yêu cầu nhập đầy đủ thông tin.
#### - Cho phép chọn máy bay thông qua [CHOOSE PLANE](#12) (special)
----------------------------------------------------------------------------------------------------------------------------------------
### ADD FLIGHT: Khởi tạo 1 chuyến bay <a name="11"></a>
![z5566112012943_29bfe96c1d27715fe8eb15a71801adae](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/586f4de2-f617-4bbf-852c-0b2a36a80e27)
#### - Yêu cầu nhập đầy đủ thông tin
#### - Cho phép chọn máy bay thông qua [CHOOSE PLANE](#12) (special)
----------------------------------------------------------------------------------------------------------------------------------------
### CHOOSE PLANE: Tính năng chọn máy bay chỉ cần thông qua click con trỏ chuột <a name="12"></a>
![z5566112012971_380046e5297c59dc2fa7d92325214d83](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/b0f4dcb8-fb39-4d86-a58f-640db764c724)
----------------------------------------------------------------------------------------------------------------------------------------
### TICKET: cho phép người dùng đặt và hủy vé. <a name="13"></a>
![z5566112048197_8d6e865c35cd5104d9442cebe415991f](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/8846a66d-e223-4e54-81a2-050a0892e671)
#### - Khung HEADER 
##### + [PASSENGER LIST](#4) (MÃ CHUYẾN BAY) dẫn đến danh sách hành khách của 1 chuyến bay. 
##### + [FLIGHT LIST](#8) quay về danh sách các chuyến bay.
|Khung thông tin chuyến bay|Special|
|--------------------------|-------|
|Hãng hàng không||
|Ngày khởi hành||
|Điểm đến||
|Điểm khởi hành||
|Giờ khởi hành||
|Thời điểm tới nơi dự kiến (special)|Cho phép cập nhật từ AVAILABLE -> COMPLETE; UNVAILABLE -> COMPLETE sau khi hoàn thành chuyến bay - Time Date|
|Loại máy bay||
|Mã máy bay||
#### - Bảng hiển thị chỗ ngồi trong máy bay. 
|Trang thái|Ý nghĩa|
|------|----------|	
|Empty| Ghế trống|
|Reserved seat| Ghế đã được đặt|
|Selected seat (Available)| Ghế đang được chọn(chưa được đặt)|
|Selected seat (unavailable)| Ghế được chọn(dã đặt)|
#### - Tính năng đặt vé máy bay - [BOOK](#14)
#### - TÍnh năng hủy vé máy bay - [CANCEL](#15)
----------------------------------------------------------------------------------------------------------------------------------------
### BOOK: Cho phép đặt vé, nhập thông tin vé, đảm bảo điền đầy đủ thông tin(1 người không thể đặt 2 vé trên cùng 1 chuyến bay). <a name="14"></a>
![z5566112048208_d0cc1f7b18326710b79f0912b5f0e780](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/c6e7108a-0200-4a3e-b5fd-874b8466d9a6)
#### - NEXT: đặt vé.
#### - Khi nhập căn cước công dân, nếu trùng với 1 hành khách đã đặt ghế trên chuyến bay hiện tại thì hệ thống sẽ báo lỗi
#### - So sánh căn cước: nếu hành khách đã từng đi ở bất kỳ chuyến bay nào trước đây, hệ thống sẽ tự điền và khóa các thông tin còn lại (Mỗi căn cước chỉ ứng với 1 người)


https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/126996254/14f33135-7f4c-4b18-aca5-6bed19df9344


----------------------------------------------------------------------------------------------------------------------------------------
### CANCEL: Hủy vé đã đặt. <a name="15"></a>
![z5566112048245_b1221a8b605ed73813201afcf180bc8d](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/46b3c959-e7c9-4803-9663-cdbe2384758d)
#### - Yêu cầu xác nhận hủy hủy vé.
#### *** Trang BOOK và CANCEL khi chọn 1 vị trí đều sẽ hiển thị chi tiết thông tin của chỗ ngồi và hành khách đã đặt tại đó.
----------------------------------------------------------------------------------------------------------------------------------------
### PASSENGER LIST: Thể hiện danh sách hành khách 1 chuyến bay đang được focus để đặt vé. <a name="16"></a>
![z5566112083251_907f2376efac7217beca076f853dbd72](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/ddf73ed7-5c9a-4615-8ae0-5695c74a15a5)
#### - Khung hearder là khung thông tin chuyến bay bao gồm: 
|Hãng hàng không|Ngày khởi hành|Điểm đến|Điểm khởi hành|Giờ khởi hành|Thời điểm tới nơi dự kiến (special)|Loại máy bay|Mã máy bay|
|-|-|-|-|-|-|-|-|
#### - Bảng danh sách chứa các thông tin của hành khách.
#### - [Ticket](#13): cho phép quay trở lại trang đặt vé của chuyến bay đang được focus.
#### - Tính năng tìm kiếm theo căn cước công dân - [KMP Algorithm](#21)
#### - Các tính năng sắp xếp danh sách hành khách theo:
|Căn cước công dân|ID|Tên|
|-|-|-|
#### - Các nút điều hướng trang dẫn tới [Flight List](#8) và [Passenger List](#4) và [ALL PASSENGER](#5)
#### - [CANCEL](#15): Chọn 1 hành khách trên danh sách danh sách hành khách 1 chuyến bay, ta có thể truy cập thẳng tới trang hủy vé của hành khách đó.
----------------------------------------------------------------------------------------------------------------------------------------
### PLANE: Thể hiện danh sách các máy bay. <a name="17"></a>
![z5566112083315_bafc700b5ed2bf14911ab027a84419f2](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/d271689f-814f-4709-8586-d3055f1de12c)
#### - Mỗi máy bay chứa các thông tin về:
|Mã máy bay|Loại máy bay|Số lượng chỗ ngồi|Trạng thái|
|-|-|-|-|
#### - Các chức năng tìm kiếm theo mã máy bay - [KMP Algorithm](#21)
#### - Các tính năng sắp xếp danh sách máy bay theo:
|ID|Số chỗ ngồi|Trạng thái|
|-|-|-|
#### - Khung "INFORMATION" chứa thông tin chi tiết của 1 máy bay.
|||
|-|-|
|[EDIT](#18)|Tính năng sửa thông tin máy bay|
|[ADD PLANE](#19)|Thêm máy bay|
|Điều Kiện|Đảm bảo đầy đủ thông tin và không trùng lặp ID, các ràng buộc về số chỗ ngồi|
#### - DELETE: Xóa 1 máy bay nào đó, đảm bảo máy bay hiện tại không thực hiện chuyến bay nào.
----------------------------------------------------------------------------------------------------------------------------------------
### EDIT: Chỉnh sửa thông tin máy bay. <a name="18"></a>
![z5566112111313_6007df5172665e8dd57956359d9a8759](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/6c400d88-3611-4cbd-832c-28592921caa0)
----------------------------------------------------------------------------------------------------------------------------------------
### ADD PLANE: Thêm 1 máy bay. <a name="19"></a>
![z5566112111356_47c946cd06d0c6717124126e1eeafc95](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/a3c6ca91-b3bb-464e-8d67-641d5d852c47)
----------------------------------------------------------------------------------------------------------------------------------------
### THỐNG KÊ: cho phép thống kê số lần thực hiện chuyến bay của các máy bay. <a name="20"></a>
![z5566112146945_b8e71197fc628e9b51fe93221a6d0965](https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/fce6b37a-068f-4213-853c-23858df3acad)
#### - Các chức năng sắp xếp theo:
|ID|Số lần thực hiện|Kiểu máy bay|
|-|-|-|
#### - Khung thông tin.
----------------------------------------------------------------------------------------------------------------------------------------
# CÁC TÍNH NĂNG NỔI BẬC TRONG ĐỒ ÁN <a name="24"></a>
## + Thuật toán tìm kiếm dựa trên KMP. <a name="21"></a>


https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/127731925/8a10fe36-8f4e-4d0a-b412-c3e9bbd536a9


## + Phân luồng chạy cập nhật chuyến bay, đồng hồ theo thời gian thực. <a name="22"></a>


https://github.com/rtwGameDev/CTDL_GIAI_THUAT/assets/126996254/58134741-96bf-41ea-a128-e7bd8e2589f3


## + Giao diện áp dụng công nghệ mới.
## + Trang bị những tiện ích liên kết các thông tin cho người dùng.
