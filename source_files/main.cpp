#include "../header_files/header.hpp"

int main(int argc, char *argv[]) {
        // mo.applyAll(argv[1]);
    QApplication app(argc, argv);
    MainImageGUI migui("/mnt/data/documents/u/ciclo_8/vision_por_computador/practicas/p2.1_reconocimiento_formas_bordes_binarizacion_filtros_operaciones_morfologicas/morphological-operations-opencv/rx-images/2.jpg");
    // migui.applyAll();
    migui.init();
    cv::waitKey(0);
    cv::destroyAllWindows();
    return app.exec();
}