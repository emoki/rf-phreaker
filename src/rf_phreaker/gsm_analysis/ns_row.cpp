/* output row functions */
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "rf_phreaker/gsm_analysis/netstart.h"


/* local function declarations */
gsm_analysis_output_list* new_row( void );

/* Added 15 May 2001 by Dhaval Dave */
void fprint_row( FILE *fp, gsm_analysis_output_list *current );

/* declared in NETSTART.C */
extern struct SuDataFileHeader suCurrentHeader;

/*****************************************************************************/

/* 
* new_row()
*
* Function to create an new output row.
* Returns a pointer to the new output row.
*/
gsm_analysis_output_list* new_row( void )
{
	gsm_analysis_output_list *tmp;

	// allocate memory for a new row.  memory is "zero'd" with calloc
	tmp = reinterpret_cast<gsm_analysis_output_list *>( calloc(sizeof(gsm_analysis_output_list), 1) );
	if( tmp == NULL )
	{
		// TODO:: some error processing here?
		;
	}

	return( tmp );
} // end of new_row()


/*****************************************************************************/
/* 
* del_rows()
*
* Function to delete all output rows.
*/
gsm_analysis_output_list* del_rows( gsm_analysis_output_list *head ) {
   gsm_analysis_output_list *tmp;

	// delete rows until we reach the end
	while( head != NULL )
	{
		// delete the row, and move to the next
		tmp = head;
		head = head->next;
		free(tmp);
	}
   return(head);
} // end of del_rows()


/*****************************************************************************/
/*
* last_row()
*
* Function to find the tail output row.
* Returns a pointer to the tail output row.
*/
gsm_analysis_output_list* last_row( gsm_analysis_output_list *head )
{
   gsm_analysis_output_list *tmp;
	tmp = head;
	if( tmp != NULL ) {
		// continue until we have the last row
		while( tmp->next != NULL )
		{
			tmp = tmp->next;
		}
	}
	return( tmp );
} // end of last_row()


/*****************************************************************************/
/*
* add_row()
*
* Function to append a new output row.
* Returns a pointer to the head row, or NULL on error.
*/
gsm_analysis_output_list* add_row( gsm_analysis_output_list *head )
{
   gsm_analysis_output_list *tmp, *tail;

	// allocate memory for a new row
	tmp = new_row();
	if( tmp == NULL ) {
		// new row was not created ->  we must be out of memory.
		// clear out all rows, and return an error condition
		head = del_rows( head );
		return(NULL);
	}
	tmp->data.NormSyncCorr = 0;
	tmp->data.BandPow = 0;

	// get the row that is currently last
	tail = last_row( head );
   
	if ( tail == NULL ) head = tmp;
	else tail->next = tmp;

	return(head);
} // end of add_row()

