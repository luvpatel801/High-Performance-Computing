
   /***********************************************
   *
   *       file d:\cips\cips.c
   *
   *       Functions: This file contains
   *          main
   *          show_menu
   *          show_image
   *
   *       Purpose:
   *          This file contains the main calling
   *          routine in the C Image Processing System.
   *
   *       External Calls:
   *          numcvrt.c - get_integer
   *          gin.c - get_image_name
   *          rtiff.c - read_tiff_image
   *          tiff.c - read_tiff_header
   *          display.c - display_image
   *                      display_menu_for_display_image
   *          pi.c - print_image
   *          ht.c - display_using_halftoning
   *                 get_threshold_value
   *          djet.c - print_graphics_image
   *                   get_graphics_caption
   *          hist.c - display_menu_for_histogram
   *                   calculate_area_histogram
   *                   print_histogram
   *                   show_histogram
   *          edge.c - detect_edges
   *                   get_edge_options
   *                   quick_edge
   *          edge2.c - homogeneity
   *                    difference_edge
   *                    contrast_edge
   *                    range
   *                    variance
   *          edge3.c - gaussian_edge
   *                    enhance_edges
   *          filter.c - filter_image
   *                     median_filter
   *                     high_pixel
   *                     low_pixel
   *                     get_filter_options
   *          addsub.c - add_image_array
   *                     subtract_image_array
   *          cutp.c - cut_image_piece
   *                   paste_image_piece
   *                   check_cut_and_paste_limits
   *          rotate.c - rotate_flip_image_array
   *          scale.c - zoom_image_array
   *          segment.c - get_segmentation_options
   *                      get_threshold_options
   *                      manual_threshold_segmentation
   *                      peak_threshold_segmentation
   *                      valley_threshold_segmentation
   *                      adaptive_threshold_segmentation
   *          boole.c - and_image
   *                    or_image
   *                    xor_image
   *                    nand_image
   *                    nor_image
   *                    not_image
   *          overlay.c - non_zero_overlay
   *                      zero_overlay
   *                      greater_overlay
   *                      less_overlay
   *                      average_overlay
   *          ed.c - erosion
   *                 dilation
   *                 mask_erosion
   *                 mask_dilation
   *                 interior_outline
   *                 exterior_outline
   *                 copy_3_x_3
   *                 opening
   *                 closing
   *                 get_shape_options
   *          morph.c - thinning
   *                    dilate_not_join
   *                    special_opening
   *                    special_closing
   *                    edm
   *                    mat
   *          txtrsubs.c - sigma
   *                       skewness
   *                       amean
   *                       adifference
   *                       hurst
   *                       compare
   *                       get_texture_options
   *          geosubs.c - geometry
   *                      arotate
   *                      get_geometry_options
   *
   *       Modifications:
   *          26 June 1990 - created
   *
   *************************************************/

#include "cips.h"


short the_image[ROWS][COLS];
short out_image[ROWS][COLS];

main()
{

   char caption[80],
        color_transform[80],
        dir_name[80],
        er_method[80],
        low_high[80],
        method[80],
        monitor_type[80],
        name[80],
        name2[80],
        name3[80],
        rep[80],
        title[80],
        ts_method[80],
        zoom_shrink[80];

   float angle     = 45.0,
         percent   = 0.5,
         x_cross   = 0.01,
         x_stretch = 1.0,
         y_cross   = 0.01,
         y_stretch = 1.0;

   int  bilinear             = 1,
        color                = 99,
        detect_threshold     = 1,
        detect_type          = 1,
        display_colors       = 16,
        element              = 1,
        filter_type          = 1,
        high                 = 100,
        horizontal           = 3,
        i                    = 0,
        ie                   = 1,
        ie2                  = 1,
        ie3                  = 1,
        il                   = 1,
        il2                  = 1,
        il3                  = 1,
        image_colors         = 256,
        invert               = 0,
        j                    = 0,
        l                    = 0,
        length               = 3,
        le                   = COLS+1,
        le2                  = COLS+1,
        le3                  = COLS+1,
        line                 = 1,
        ll                   = ROWS+1,
        ll2                  = ROWS+1,
        ll3                  = ROWS+1,
        m                    = COLS/2,
        n                    = ROWS/2,
        not_finished         = 1,
        number               = 1,
        print                = 0,
        response             = 99,
        rotation_type        = 1,
        scale                = 2,
        show_hist            = 0,
        size                 = 7,
        threshold            = 128,
        vertical             = 3,
        width                = 3,
        x_control            = 50,
        y_control            = 50,
        x1                   = 10,
        y1                   = 10,
        x2                   = 90,
        y2                   = 10,
        x3                   = 90,
        y3                   = 90,
        x4                   = 10,
        y4                   = 90;

   long     mean_of_pixels;

   unsigned long histogram[256];

   short    diff        = 10,
            erode       = 3,
            hi          = 255,
            low         = 0,
            min_area    = 10,
            max_area    = 1000,
            value       = 200,
            x_displace  = 10,
            y_displace  = 10,
            low_hi_filter[3][3];

   struct   tiff_header_struct image_header;


   my_clear_text_screen();

   strcpy(color_transform, "Straight mode");
   strcpy(monitor_type, "VGA");
   strcpy(low_high, "l");
   strcpy(zoom_shrink, "z");
   strcpy(method, "r");
   strcpy(title, "");
   strcpy(ts_method, "manual");
   strcpy(er_method, "edge");

   strcpy(name,  "c:/pix/adam256.tif");
   strcpy(name2, "c:/pix/output.tif");
   strcpy(name3, "c:/pix/output.tif");
   strcpy(dir_name, "c:/pix");

     while(not_finished){

        show_menu();

        get_integer(&response);

        switch (response){

        case 1:/* display image header */
         get_image_name(name);
         read_tiff_header(name, &image_header);
         printf("\n\nCIPS> The image header is:");
         printf("\n\t\twidth=%ld length=%ld  start=%ld  bits=%ld",
              image_header.image_width,
              image_header.image_length,
              image_header.strip_offset,
              image_header.bits_per_pixel);
         printf("\nCIPS> Hit Enter to continue");
         gets(rep);
        break;

        case 2:/* display image numbers */
         get_image_name(name);
         get_parameters(&il, &ie, &ll, &le);
         read_tiff_image(name, the_image, il, ie, ll, le);
         show_image(the_image, il, ie);
         break;

        case 3:   /* print image numbers */
         get_image_name(name);
         get_parameters(&il, &ie, &ll, &le);
         read_tiff_image(name, the_image, il, ie, ll, le);
         print_image(the_image, name, 1, 1, 1, 100, 18,
                     il, ie);
        break;

        case 4:   /* display image */
         get_image_name(name);
         read_tiff_header(name, &image_header);
         get_parameters(&il, &ie, &ll, &le);
         display_menu_for_display_image(&image_colors,
                   &display_colors, &invert,
                   color_transform, monitor_type,
                   &show_hist);
         printf("\nEnter title>");
         gets(title);
         display_image(name, the_image, il, ie,
                   ll, le, &image_header, monitor_type,
                   color_transform, invert,
                   image_colors, display_colors,
                   show_hist, title);
        break;

        case 5:   /* display image using halftoning */
         get_image_name(name);
         read_tiff_header(name, &image_header);
         get_parameters(&il, &ie, &ll, &le);
         display_menu_for_display_image(&image_colors,
                   &display_colors, &invert,
                   color_transform, monitor_type,
                   &show_hist);
         get_threshold_value(&threshold, &print);
         display_using_halftoning(the_image, name,
                   il, ie, ll, le, threshold,
                   invert, image_colors, &image_header,
                   monitor_type, print, show_hist,
                   color_transform);
        break;

        case 6:   /* print graphics image */
         get_image_name(name);
         read_tiff_header(name, &image_header);
         get_parameters(&il, &ie, &ll, &le);
         display_menu_for_display_image(&image_colors,
                   &display_colors, &invert,
                   color_transform, monitor_type,
                   &show_hist);
         get_graphics_caption(caption);
         print_graphics_image(the_image, out_image,
                   name, il, ie, ll, le, image_colors,
                   invert, caption, show_hist,
                   color_transform);
        break;
        case 7:   /* print or display histogram numbers */
         get_image_name(name);
         read_tiff_header(name, &image_header);
         get_parameters(&il, &ie, &ll, &le);
         display_menu_for_histogram(&print, &vertical,
                   &horizontal);
         calculate_area_histogram(histogram, vertical,
                   horizontal, the_image, name,
                   il, ie, ll, le);
         if(print == 0)
            show_histogram(histogram);
         if(print == 1)
            print_histogram(histogram, name);
        break;

        case 8:  /* perform edge detection */
         printf("\nCIPS> Enter input image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name2);
         get_parameters(&il, &ie, &ll, &le);
         get_edge_options(&detect_type,
                          &detect_threshold,
                          &high, &size);
         if(detect_type == 1  ||
            detect_type == 2  ||
            detect_type == 3)
            detect_edges(name, name2, the_image,
                         out_image, il, ie, ll, le,
                         detect_type, detect_threshold,
                         high);
         if(detect_type == 4)
            quick_edge(name, name2, the_image, out_image,
                       il, ie, ll, le, detect_threshold,
                       high);
         if(detect_type == 5)
              homogeneity(name, name2, the_image, out_image,
                       il, ie, ll, le, detect_threshold,
                       high);
         if(detect_type == 6)
              difference_edge(name, name2, the_image,
                              out_image, il, ie, ll,
                              le, detect_threshold,
                              high);
         if(detect_type == 7)
              contrast_edge(name, name2, the_image,
                            out_image, il, ie, ll,
                            le, detect_threshold,
                            high);
         if(detect_type == 8)
              gaussian_edge(name, name2, the_image,
                            out_image, il, ie, ll,
                            le, size,
                            detect_threshold, high);
         if(detect_type == 10)
              range(name, name2, the_image, out_image,
                    il, ie, ll, le, size,
                    detect_threshold, high);
         if(detect_type == 11)
              variance(name, name2, the_image,
                       out_image, il, ie, ll, le,
                       detect_threshold, high);
         break;

        case 9: /* perform edge enhancement */
         printf("\nCIPS> Enter input image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name2);
         get_parameters(&il, &ie, &ll, &le);
         printf("\nCIPS> Enter high threshold parameter");
         printf(" \n\t___\b\b\b");
         get_integer(&high);
         enhance_edges(name, name2, the_image,
                       out_image, il, ie, ll, le,
                       high);
         break;

        case 10: /* perform image filtering */
         printf("\nCIPS> Enter input image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name2);
         get_parameters(&il, &ie, &ll, &le);
         get_filter_options(&filter_type, low_high);
         if(low_high[0] == 'l' ||
             low_high[0] == 'L' ||
             low_high[0] == 'h' ||
             low_high[0] == 'H'){
            setup_filters(filter_type, low_high,
                          low_hi_filter);
            filter_image(name, name2, the_image,
                         out_image, il, ie, ll, le,
                         low_hi_filter, filter_type);
         }

         if(low_high[0] == 'm' ||
             low_high[0] == 'M')
               median_filter(name, name2, the_image,
                             out_image, il, ie, ll,
                             le, filter_type);

         if(low_high[0] == 'i' ||
             low_high[0] == 'I')
               high_pixel(name, name2, the_image,
                          out_image, il, ie, ll, le,
                          filter_type);

         if(low_high[0] == 'o' ||
             low_high[0] == 'O')
               low_pixel(name, name2, the_image,
                         out_image, il, ie, ll, le,
                         filter_type);

        break;

        case 11: /* perform image addition and
                    subtraction */
         printf("\nCIPS> Image Addition:"
              "\n         output = first + second"
              "\n      Image Subtractions:"
              "\n         output = first - second");
         printf("\nCIPS> Enter first image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter second image name\n");
         get_image_name(name2);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name3);
         printf("\nCIPS> Enter parameters for first image");
         get_parameters(&il, &ie, &ll, &le);
         printf("\nCIPS> Enter parameters for second image");
         get_parameters(&il2, &ie2, &ll2, &le2);
         printf("\nCIPS> Enter parameters for output image");
         get_parameters(&il3, &ie3, &ll3, &le3);
         printf("\n\nCIPS> Enter a=addition    "
                "s=subtraction\n");
         printf("\nCIPS> _\b");
         gets(low_high);
         if(low_high[0] == 'a' || low_high[0] == 'A')
            add_image_array(name, name2, name3,
                the_image, out_image,
                il, ie, ll, le,
                il2, ie2, ll2, le2,
                il3, ie3, ll3, le3);
         if(low_high[0] == 's' || low_high[0] == 'S')
            subtract_image_array(name, name2, name3,
                the_image, out_image,
                il, ie, ll, le,
                il2, ie2, ll2, le2,
                il3, ie3, ll3, le3);
        break;

        case 12: /* image cutting and pasting */
         printf("\n\nCIPS> Cut from source image and "
                "paste to destination image");
         printf("\nCIPS> Enter source image name");
         get_image_name(name);
         get_parameters(&il, &ie, &ll, &le);
         check_cut_and_paste_limits(&il, &ie, &ll, &le);
         cut_image_piece(name, the_image,
                         il, ie, ll, le);
         printf("\nCIPS> Enter destination image name");
         get_image_name(name2);
         printf("\nCIPS> Enter destination image "
                "parameters");
         get_parameters(&il, &ie, &ll, &le);
         check_cut_and_paste_limits(&il, &ie, &ll, &le);
         paste_image_piece(name2, name, the_image,
                           out_image, il, ie, ll, le);
        break;

        case 13: /* image rotation and flipping */
         printf("\nCIPS> Enter source image name");
         get_image_name(name);
         get_parameters(&il, &ie, &ll, &le);
         printf("\nCIPS> Enter destination image name");
         printf("\nCIPS> (source can equal destination)");
         get_image_name(name2);
         printf("\nCIPS> Enter destination image "
                "parameters");
         get_parameters(&il2, &ie2, &ll2, &le2);
         printf("\nCIPS> Enter number of Rotations "
                "(1, 2, 3)");
         printf("\nCIPS> or type of Flip "
                "(4=horizontal 5=vertical)");
         printf("\nCIPS> __\b");
         get_integer(&rotation_type);
         rotate_flip_image_array(name, name2,
                                 the_image,
                                 out_image, il, ie,
                                 ll, le, il2, ie2,
                                 ll2, le2,
                                 rotation_type);
        break;

        case 14: /* image scaling */
         printf("\nCIPS> Enter input image name");
         get_image_name(name);
         get_parameters(&il, &ie, &ll, &le);
         printf("\nCIPS> Enter output image name");
         get_image_name(name2);
         get_scaling_options(zoom_shrink, &scale, method);
         if(zoom_shrink[0] == 'z' || zoom_shrink[0] == 'Z')
            zoom_image_array(name, name2, the_image,
                             out_image, il, ie, ll,
                             le, scale, method);
         if(zoom_shrink[0] == 's' ||
            zoom_shrink[0] == 'S'){
             printf("\nCIPS> Enter output image "
                     "parameters");
               get_parameters(&il2, &ie2, &ll2, &le2);
             shrink_image_array(name, name2, the_image,
                                out_image, il, ie, ll,
                                le, il2, ie2, ll2, le2,
                                scale, method);
         }
        break;

        case 15: /* create image */
         printf("\nCIPS> Enter input name of image "
                "to create");
         get_image_name(name);
         printf("\nCIPS> Enter number of %d blocks "
                "wide",COLS);
         printf("\n      ___\b\b");
         get_integer(&width);
         printf("\nCIPS> Enter number of %d blocks "
                "tall",ROWS);
         printf("\n      ___\b\b");
         get_integer(&length);
         image_header.lsb            = 1;
         image_header.bits_per_pixel = 8;
         image_header.image_length   = length*COLS;
         image_header.image_width    = width*ROWS;
         image_header.strip_offset   = 1000;
         for(i=0; i<ROWS; i++)
            for(j=0; j<COLS; j++)
               the_image[i][j] = 0;
         create_allocate_tiff_file(name, &image_header,
                                   the_image);
        break;

        case 16: /* image thresholding */
         printf("\nCIPS> Enter input image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name2);
         get_parameters(&il, &ie, &ll, &le);
         get_threshold_options(ts_method, &hi,
                               &low, &value);
         if(ts_method[0] == 'm' ||
            ts_method[0] == 'M')
            manual_threshold_segmentation(name,
                   name2, the_image, out_image,
                   il, ie, ll, le,
                   hi, low, value, 0);
         if(ts_method[0] == 'p' ||
            ts_method[0] == 'P')
            peak_threshold_segmentation(name,
                   name2, the_image, out_image,
                   il, ie, ll, le, value, 0);
         if(ts_method[0] == 'v' ||
            ts_method[0] == 'V')
            valley_threshold_segmentation(name,
                   name2, the_image, out_image,
                   il, ie, ll, le, value, 0);
         if(ts_method[0] == 'a' ||
            ts_method[0] == 'a')
            adaptive_threshold_segmentation(name,
                   name2, the_image, out_image,
                   il, ie, ll, le, value, 0);
        break;

        case 17: /* image segmentation */
         printf("\nCIPS> Enter input image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name2);
         get_parameters(&il, &ie, &ll, &le);
         get_segmentation_options(ts_method, &hi,
                                  &low, &value);
         if(ts_method[0] == 'm' ||
            ts_method[0] == 'M')
            manual_threshold_segmentation(name,
                   name2, the_image, out_image,
                   il, ie, ll, le,
                   hi, low, value, 1);
         if(ts_method[0] == 'p' ||
            ts_method[0] == 'P')
            peak_threshold_segmentation(name,
                   name2, the_image, out_image,
                   il, ie, ll, le, value, 1);
         if(ts_method[0] == 'v' ||
            ts_method[0] == 'V')
            valley_threshold_segmentation(name,
                   name2, the_image, out_image,
                   il, ie, ll, le, value, 1);
         if(ts_method[0] == 'a' ||
            ts_method[0] == 'a')
            adaptive_threshold_segmentation(name,
                   name2, the_image, out_image,
                   il, ie, ll, le, value, 1);
        break;

        case 18: /* edge & gray shade segmentation */
         printf("\nCIPS> Enter input image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name2);
         get_parameters(&il, &ie, &ll, &le);
         get_edge_region_options(er_method,
             &detect_type, &min_area, &max_area,
             &value, &diff, &percent, &erode);
         if(er_method[0] == 'e' ||
            er_method[0] == 'E')
            edge_region(name, name2, the_image,
                        out_image, il, ie, ll, le,
                        detect_type, min_area,
                        max_area, diff, percent,
                        value, erode);
         if(er_method[0] == 'g' ||
            er_method[0] == 'G')
            gray_shade_region(name, name2, the_image,
                        out_image, il, ie, ll, le,
                        diff, min_area, max_area);
         if(er_method[0] == 'c' ||
            er_method[0] == 'C')
            edge_gray_shade_region(name, name2,
                        the_image, out_image,
                        il, ie, ll, le, detect_type,
                        min_area, max_area, diff,
                        percent, value, erode);
        break;

        case 19: /* Boolean operations */
         printf("\nCIPS> Boolean operations:"
                "\n      output = first OP second"
                "\n      If using NOT operation, "
                "\n      only enter one set of"
                "\n      parameters.");
         printf("\nCIPS> Enter first image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter second image name\n");
         get_image_name(name2);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name3);
         printf("\nCIPS> Enter parameters for first image");
         get_parameters(&il, &ie, &ll, &le);
         printf("\nCIPS> Enter parameters for second image");
         get_parameters(&il2, &ie2, &ll2, &le2);
         printf("\nCIPS> Enter parameters for output image");
         get_parameters(&il3, &ie3, &ll3, &le3);
         printf("\n\nCIPS> Enter operation: and or xor nand nor"
                " not\n");
         gets(low_high);

         if(strncmp("and", low_high, 3) == 0){
            and_image(name, name2, name3,
                      the_image, out_image,
                      il,  ie,  ll,  le,
                      il2, ie2, ll2, le2,
                      il3, ie3, ll3, le3);
         }
         if(strncmp("or", low_high, 2) == 0){
            or_image(name, name2, name3,
                     the_image, out_image,
                     il,  ie,  ll,  le,
                     il2, ie2, ll2, le2,
                     il3, ie3, ll3, le3);
         }
         if(strncmp("xor", low_high, 3) == 0){
            xor_image(name, name2, name3,
                      the_image, out_image,
                      il,  ie,  ll,  le,
                      il2, ie2, ll2, le2,
                      il3, ie3, ll3, le3);
         }
         if(strncmp("nand", low_high, 4) == 0){
            printf("\nEnter the value of ON pixel");
            printf("\n\t___\b\b\b");
            get_short(&value);
            nand_image(name, name2, name3,
                       the_image, out_image,
                       il,  ie,  ll,  le,
                       il2, ie2, ll2, le2,
                       il3, ie3, ll3, le3, value);
         }
         if(strncmp("nor", low_high, 3) == 0){
            printf("\nEnter the value of ON pixel");
            printf("\n\t___\b\b\b");
            get_short(&value);
            nor_image(name, name2, name3,
                      the_image, out_image,
                      il,  ie,  ll,  le,
                      il2, ie2, ll2, le2,
                      il3, ie3, ll3, le3, value);
         }
         if(strncmp("not", low_high, 3) == 0){
            printf("\nEnter the value of ON pixel");
            printf("\n\t___\b\b\b");
            get_short(&value);
            not_image(name, name2, name3,
                      the_image, out_image,
                      il,  ie,  ll,  le, value);
         }
        break;

        case 20: /* overlay operations */
         printf("\nCIPS> Overlay operations:"
                "\n      output = first OP second");
         printf("\nCIPS> Enter first image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter second image name\n");
         get_image_name(name2);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name3);
         printf("\nCIPS> Enter parameters for first image");
         get_parameters(&il, &ie, &ll, &le);
         printf("\nCIPS> Enter parameters for second image");
         get_parameters(&il2, &ie2, &ll2, &le2);
         printf("\nCIPS> Enter parameters for output image");
         get_parameters(&il3, &ie3, &ll3, &le3);
         printf("\n\nCIPS> Enter: non-zero zero "
                "greater less average\n");
         gets(low_high);

         if(strncmp("non", low_high, 3) == 0){
            non_zero_overlay(name, name2, name3,
                             the_image, out_image,
                             il,  ie,  ll,  le,
                             il2, ie2, ll2, le2,
                             il3, ie3, ll3, le3);
         }
         if(strncmp("zero", low_high, 4) == 0){
            zero_overlay(name, name2, name3,
                         the_image, out_image,
                         il,  ie,  ll,  le,
                         il2, ie2, ll2, le2,
                         il3, ie3, ll3, le3);
         }
         if(strncmp("gre", low_high, 3) == 0){
            greater_overlay(name, name2, name3,
                            the_image, out_image,
                             il,  ie,  ll,  le,
                             il2, ie2, ll2, le2,
                            il3, ie3, ll3, le3);
         }
         if(strncmp("less", low_high, 4) == 0){
            less_overlay(name, name2, name3,
                         the_image, out_image,
                         il,  ie,  ll,  le,
                         il2, ie2, ll2, le2,
                         il3, ie3, ll3, le3);
         }
         if(strncmp("ave", low_high, 3) == 0){
            average_overlay(name, name2, name3,
                             the_image, out_image,
                            il,  ie,  ll,  le,
                            il2, ie2, ll2, le2,
                            il3, ie3, ll3, le3);
         }
        break;

        case 21: /* shape operations */
         printf("\nCIPS> Enter input image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name2);
         get_parameters(&il, &ie, &ll, &le);
         get_shape_options(low_high, &value,
                           &threshold, &number);
         if(strncmp("thi", low_high, 3) == 0){
            thinning(name, name2, the_image, out_image,
                     il, ie, ll, le,
                     value, threshold, 0);
         }
         if(strncmp("dnj", low_high, 3) == 0){
            dilate_not_join(name, name2, the_image,
                            out_image, il, ie, ll, le,
                            value, threshold);
         }
         if(strncmp("ero", low_high, 3) == 0){
            erosion(name, name2, the_image, out_image,
                    il, ie, ll, le, value, threshold);
         }
         if(strncmp("dil", low_high, 3) == 0){
            dilation(name, name2, the_image, out_image,
                     il, ie, ll, le, value, threshold);
         }
         if(strncmp("mer", low_high, 3) == 0){
            mask_erosion(name, name2, the_image,
                         out_image, il, ie, ll, le,
                         value, threshold);
         }
         if(strncmp("mdi", low_high, 3) == 0){
            mask_dilation(name, name2, the_image,
                          out_image, il, ie, ll, le,
                          value, threshold);
         }
         if(strncmp("int", low_high, 3) == 0){
            interior_outline(name, name2, the_image,
                             out_image, il, ie, ll, le,
                             value, threshold);
         }
         if(strncmp("ext", low_high, 3) == 0){
            exterior_outline(name, name2, the_image,
                             out_image, il, ie, ll, le,
                             value, threshold);
         }
         if(strncmp("ope", low_high, 3) == 0){
            opening(name, name2, the_image, out_image,
                    il, ie, ll, le, value, threshold,
                    number);
         }
         if(strncmp("clo", low_high, 3) == 0){
            closing(name, name2, the_image, out_image,
                    il, ie, ll, le, value, threshold,
                    number);
         }
         if(strncmp("spo", low_high, 3) == 0){
            special_opening(name, name2, the_image,
                            out_image, il, ie, ll, le,
                            value, threshold,
                            number);
         }
         if(strncmp("spc", low_high, 3) == 0){
            special_closing(name, name2, the_image,
                            out_image, il, ie, ll, le,
                            value, threshold,
                            number);
         }
         if(strncmp("edm", low_high, 3) == 0){
            edm(name, name2, the_image, out_image,
                il, ie, ll, le, value);
         }
         if(strncmp("mat", low_high, 3) == 0){
            edm(name, name2, the_image, out_image,
                il, ie, ll, le, value);
         }
        break;

        case 22: /* texture operations */
         printf("\nCIPS> Enter input image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name2);
         get_parameters(&il, &ie, &ll, &le);
         get_texture_options(low_high, &threshold,
                             &value, &size,
                             &line, &element);
         if(strncmp(low_high, "compare", 3) == 0)
            compare(name, name2, the_image, out_image,
                    il, ie, ll, le,
                    line, element, size);
         if(strncmp(low_high, "hurst", 3) == 0)
            hurst(name, name2, the_image, out_image,
                  il, ie, ll, le, size);
         if(strncmp(low_high, "adifference", 3) == 0)
            adifference(name, name2, the_image,
                        out_image, il+i*ROWS,
                        ie, ll, le, size);
         if(strncmp(low_high, "amean", 3) == 0)
            amean(name, name2, the_image, out_image,
                  il, ie, ll, le, size);
         if(strncmp(low_high, "skewness", 3) == 0)
            skewness(name, name2, the_image, out_image,
                     il, ie, ll, le, size, 
                     threshold, value);
         if(strncmp(low_high, "sigma", 3) == 0)
            sigma(name, name2, the_image, out_image,
                  il, ie, ll, le, size, 
                  threshold, value);

        break;

        case 23:  /* geometry operations */
         printf("\nCIPS> Enter input image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name2);
         get_parameters(&il, &ie, &ll, &le);
         get_geometry_options(
                     method, &angle, 
                     &x_displace, &y_displace, 
                     &x_stretch, &y_stretch, 
                     &x_cross,  &y_cross, 
                     &bilinear, &m, &n);
         if(strncmp(method, "geometry", 3) == 0)
            geometry(name, name2, 
                  the_image, out_image,
                  il, ie, ll, le, angle, 
                  x_stretch, y_stretch,
                  x_displace, y_displace,
                  x_cross, y_cross,
                  bilinear);
         if(strncmp(method, "rotate", 3) == 0)
            arotate(name, name2, 
                  the_image, out_image,
                  il, ie, ll, le,
                  angle, m, n, bilinear);
        break;

        case 24:  /* warp operations */
         printf("\nCIPS> Enter input image name\n");
         get_image_name(name);
         printf("\nCIPS> Enter output image name\n");
         get_image_name(name2);
         get_parameters(&il, &ie, &ll, &le);
         get_warp_options(method, &bilinear, 
                 &x_control, &y_control,
                 &x1, &y1, &x2, &y2, 
                 &x3, &y3, &x4, &y4);
         if(strncmp(method, "warp", 3) == 0)
            warp(name, name2, 
              the_image, out_image,
                 il, ie, ll, le,
                 x_control, y_control,
                 bilinear);
         if(strncmp(method, "object-warp", 3) == 0)
            object_warp(name, name2, 
               the_image, out_image,
                  il, ie, ll, le, 
                  x1, y1, x2, y2, 
                  x3, y3, x4, y4,
                  bilinear);
        break;

        case 30:  /* exit system */
         not_finished = 0;
        break;

        default:
         printf("\nCould not understand response, "
                "try again");
        break;

     }               /* ends switch response */
  }               /* ends while not finished */
}               /* ends main                 */






   /*************************************************
   *
   *   show_image(...
   *
   *   This function displays the image numbers on the
   *   screen as text.  It displays 20 rows  with 18
   *   columns each.
   *
   **************************************************/

show_image(image, il, ie)
   int   il, ie;
   short image[ROWS][COLS];
{
   int i, j;
   printf("\n   ");
   for(i=0; i<18; i++)
      printf("-%3d", i+ie);

   for(i=0; i<20; i++){
      printf("\n%2d>", i+il);
      for(j=0; j<18; j++)
         printf("-%3d", image[i][j]);
   }

   printf("\nPress enter to continue");
   get_integer(&i);

}  /* ends show_image  */





   /*************************************************
   *
   *   show_menu(..
   *
   *   This function displays the CIPS main menu.
   *
   **************************************************/

show_menu()
{

 printf(""
 "\n\n\t\t\tWelcome to CIPS"
 "\n\t\tThe C Image Processing System"
 "\n\t\tDwayne Phillips 1990-1993"
 "\nThese are your choices:"
 "\n1.  Display image header               13. Image rotate & flip" 
 "\n2.  Show image numbers                 14. Image scaling"    
 "\n3.  Print image numbers                15. Create blank image" 
 "\n4.  Display (EGA & VGA)                16. Image thresholding"
 "\n5.  Display or print using halftoning  17. Image segmentation"
 "\n6.  Print using dithering              18. Edge & gray segmentation"
 "\n7.  Print or display histogram         19. Boolean operations"
 "\n8.  Edge Detection                     20. Image overlay"
 "\n9.  Edge Enhancement                   21. Shape operations"  
 "\n10. Image filtering                    22. Texture operations"
 "\n11. Image add & subtract               23. Geometry operations" 
 "\n12 Image cut & paste                   24. Warp operations"
 "\n30. Exit system\n"
 "\nEnter choice __\b\b");

}  /* ends show_menu */
