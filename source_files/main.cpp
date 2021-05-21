#include "../header_files/header.hpp"

int main(int argc, char *argv[]) {
        // mo.applyAll(argv[1]);
    MainImageGUI migui("/mnt/data/documents/u/ciclo_8/vision_por_computador/practicas/p2.1_reconocimiento_formas_bordes_binarizacion_filtros_operaciones_morfologicas/morphological-operations-opencv/rx-images/3.jpg", argc, argv);
    migui.applyAll();

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}