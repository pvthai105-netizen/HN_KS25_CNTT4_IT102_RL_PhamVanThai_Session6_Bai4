
#include <stdio.h>
#include <string.h>

#define MAX 100

int main(void) {
    char maSach[MAX][20];
    char tenSach[MAX][100];
    int tongSoLuong[MAX];
    int dangMuon[MAX];
    float giaBia[MAX];

    int soLuong = 0;
    int luaChon;

    do {
        printf("\n========== QUAN LY KHO SACH ==========\n");
        printf("1. Them dau sach moi\n");
        printf("2. Hien thi danh sach kho sach\n");
        printf("3. Ghi nhan muon / tra sach\n");
        printf("4. Xoa dau sach\n");
        printf("5. Thong ke kho sach\n");
        printf("0. Thoat chuong trinh\n");
        printf("======================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &luaChon);

        switch (luaChon) {

            // CASE 1: THEM SACH
            case 1: {
                if (soLuong >= MAX) {
                    printf("Kho sach da day!\n");
                    break;
                }

                char maMoi[20];
                int trung = 0;

                printf("Nhap ma sach: ");
                scanf("%19s", maMoi);

                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maSach[i], maMoi) == 0) {
                        trung = 1;
                        break;
                    }
                }

                if (trung == 1) {
                    printf("Ma sach da ton tai!\n");
                    break;
                }

                strcpy(maSach[soLuong], maMoi);

                while (getchar() != '\n');

                printf("Nhap ten sach: ");
                fgets(tenSach[soLuong], sizeof(tenSach[soLuong]), stdin);

                tenSach[soLuong][strcspn(tenSach[soLuong], "\n")] = '\0';

                printf("Nhap tong so luong: ");
                scanf("%d", &tongSoLuong[soLuong]);

                if (tongSoLuong[soLuong] <= 0) {
                    printf("So luong phai lon hon 0!\n");
                    break;
                }

                printf("Nhap gia bia (VND): ");
                scanf("%f", &giaBia[soLuong]);

                if (giaBia[soLuong] <= 0) {
                    printf("Gia bia phai lon hon 0!\n");
                    break;
                }

                dangMuon[soLuong] = 0;
                soLuong++;

                printf("Them sach thanh cong!\n");
                break;
            }

            // CASE 2: HIEN THI DANH SACH
            case 2: {
                if (soLuong == 0) {
                    printf("Kho sach hien dang rong!\n");
                    break;
                }

                printf("\n%-5s %-15s %-30s %-12s %-12s %-12s %-15s\n",
                       "STT", "Ma sach", "Ten sach",
                       "Tong SL", "Dang muon", "Kha dung", "Gia bia");

                for (int i = 0; i < soLuong; i++) {
                    int khaDung = tongSoLuong[i] - dangMuon[i];

                    printf("%-5d %-15s %-30s %-12d %-12d %-12d %-15.2f\n",
                           i + 1,
                           maSach[i],
                           tenSach[i],
                           tongSoLuong[i],
                           dangMuon[i],
                           khaDung,
                           giaBia[i]);
                }

                break;
            }

            // CASE 3: MUON / TRA SACH
            case 3: {
                if (soLuong == 0) {
                    printf("Kho sach hien dang rong!\n");
                    break;
                }

                char maCanTim[20];
                int pos = -1;

                printf("Nhap ma sach can thao tac: ");
                scanf("%19s", maCanTim);

                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maSach[i], maCanTim) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay sach!\n");
                    break;
                }

                printf("Tim thay sach: %s\n", tenSach[pos]);
                printf("Dang muon: %d quyển\n", dangMuon[pos]);

                int thaoTac;
                printf("Chon thao tac (1-Muon, 2-Tra): ");
                scanf("%d", &thaoTac);

                if (thaoTac == 1) {
                    int soMuon;
                    int khaDung = tongSoLuong[pos] - dangMuon[pos];

                    printf("So luong kha dung: %d\n", khaDung);
                    printf("Nhap so luong muon: ");
                    scanf("%d", &soMuon);

                    if (soMuon <= 0) {
                        printf("So luong muon phai lon hon 0!\n");
                    } else if (soMuon > khaDung) {
                        printf("Khong du sach trong kho!\n");
                    } else {
                        dangMuon[pos] += soMuon;
                        printf("Muon sach thanh cong!\n");
                    }

                } else if (thaoTac == 2) {
                    int soTra;
                    int soNgayQuaHan;

                    printf("Nhap so luong tra: ");
                    scanf("%d", &soTra);

                    if (soTra <= 0) {
                        printf("So luong tra phai lon hon 0!\n");
                        break;
                    }

                    if (soTra > dangMuon[pos]) {
                        printf("So luong tra vuot qua so sach dang muon!\n");
                        break;
                    }

                    printf("Nhap so ngay qua han (0 neu dung han): ");
                    scanf("%d", &soNgayQuaHan);

                    if (soNgayQuaHan < 0) {
                        printf("So ngay qua han khong hop le!\n");
                        break;
                    }

                    int tienPhat = soTra * soNgayQuaHan * 5000;

                    dangMuon[pos] -= soTra;

                    printf("\n--- BIEN NHAN TRA SACH ---\n");
                    printf("Tra thanh cong: %d quyen.\n", soTra);

                    if (soNgayQuaHan > 0) {
                        printf("Qua han: %d ngay.\n", soNgayQuaHan);
                        printf("Tien phat: %d VND.\n", tienPhat);
                    } else {
                        printf("Tra sach dung han, khong co tien phat.\n");
                    }

                } else {
                    printf("Lua chon khong hop le!\n");
                }

                break;
            }

            // CASE 4: XOA SACH
            case 4: {
                if (soLuong == 0) {
                    printf("Kho sach hien dang rong!\n");
                    break;
                }

                char maCanXoa[20];
                int pos = -1;

                printf("Nhap ma sach can xoa: ");
                scanf("%19s", maCanXoa);

                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maSach[i], maCanXoa) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay sach!\n");
                    break;
                }

                if (dangMuon[pos] > 0) {
                    printf("Sach dang cho muon, khong the xoa!\n");
                    break;
                }

                for (int i = pos; i < soLuong - 1; i++) {
                    strcpy(maSach[i], maSach[i + 1]);
                    strcpy(tenSach[i], tenSach[i + 1]);
                    tongSoLuong[i] = tongSoLuong[i + 1];
                    dangMuon[i] = dangMuon[i + 1];
                    giaBia[i] = giaBia[i + 1];
                }

                soLuong--;

                printf("Xoa sach thanh cong!\n");
                break;
            }

            // CASE 5: THONG KE KHO
            case 5: {
                int tongBanSach = 0;
                int tongDangMuon = 0;
                float tongGiaTri = 0;

                for (int i = 0; i < soLuong; i++) {
                    tongBanSach += tongSoLuong[i];
                    tongDangMuon += dangMuon[i];
                    tongGiaTri += tongSoLuong[i] * giaBia[i];
                }

                printf("\n===== BAO CAO THONG KE KHO =====\n");
                printf("So dau sach: %d\n", soLuong);
                printf("Tong so ban sach: %d\n", tongBanSach);
                printf("Tong so sach dang muon: %d\n", tongDangMuon);
                printf("Tong so sach kha dung: %d\n",
                       tongBanSach - tongDangMuon);
                printf("Tong gia tri tai san: %.2f VND\n", tongGiaTri);
                printf("================================\n");

                break;
            }

            case 0:
                printf("Dang thoat chuong trinh...\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (luaChon != 0);

    return 0;
}