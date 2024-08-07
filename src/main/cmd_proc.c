#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vicNl.h>

static char vcid[] = "$Id: cmd_proc.c,v 4.3.2.2 2012/02/05 00:15:44 vicadmin Exp $";

filenames_struct cmd_proc(int argc, char *argv[]) 
{
//fprintf(stderr,"in cmd_proc argc is %d\n",argc);
  extern option_struct options;
  extern int getopt();
  extern char *optarg;
  extern int optind; 
  extern char *optstring;

  filenames_struct names;
  int              optchar;
  char             GLOBAL_SET;
  
  if(argc==1) {
    usage(argv[0]);
    exit(1);
  }
  
  GLOBAL_SET = FALSE;

 optind=1;
 while((optchar = getopt(argc, argv, optstring)) != EOF) {
    //fprintf(stderr,"%c\n",(char)optchar);
    //fprintf(stderr,"%d\n",optchar);
    switch((char)optchar) {
    case 'v':
      /** Version information **/
      display_current_settings(DISP_VERSION,(filenames_struct*)NULL,(global_param_struct*)NULL);
      exit(0);
      break;
    case 'o':
      /** Compile-time options information **/
      display_current_settings(DISP_COMPILE_TIME,(filenames_struct*)NULL,(global_param_struct*)NULL);
      exit(0);
      break;
    case 'g':
      /** Global Parameters File **/
      strcpy(names.global, optarg);
      GLOBAL_SET = TRUE;
      break;
    default:
      /** Print Usage if Invalid Command Line Arguments **/
      usage(argv[0]);
      exit(1);
      break;
    }
  }

  if(!GLOBAL_SET) {
    fprintf(stderr,"ERROR: Must set global control file using the '-g' flag\n");
    usage(argv[0]);
    exit(1);
  }

  return names;
}


void usage(char *temp)
/**********************************************************************
	usage		Keith Cherkauer		May 27, 1996

  This routine prints out usage details.

**********************************************************************/
{
  fprintf(stderr,"Usage: %s [-v | -o | -g<global_parameter_file>]\n",temp);
  fprintf(stderr,"  v: display version information\n");
  fprintf(stderr,"  o: display compile-time options settings (set in user_def.h)\n");
  fprintf(stderr,"  g: read model parameters from <global_parameter_file>.\n");
  fprintf(stderr,"       <global_parameter_file> is a file that contains all needed model\n");
  fprintf(stderr,"       parameters as well as model option flags, and the names and\n");
  fprintf(stderr,"       locations of all other files.\n");
}
