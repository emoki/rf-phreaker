#if !defined _NS_ROW_H
#define _NS_ROW_H


/*  */

/*****************************************************************************/


/*****************************************************************************/

/* function prototypes from ns_row.c */

gsm_analysis_output_list* del_rows( gsm_analysis_output_list *head );
gsm_analysis_output_list* last_row( gsm_analysis_output_list *head );
gsm_analysis_output_list* add_row( gsm_analysis_output_list *head );
void print_rows( gsm_analysis_output_list *head );



/*****************************************************************************/

#endif