CMD	= tomoJointBSvpvs
CC	= gcc
#FC	= g77
FC	= gfortran
SRCS	= main.f\
	  aprod.f cluster1.f covar.f datum.f \
	  delaz.f delaz2.f direct1.f dist.f exist.f \
	  freeunit.f ifindi.f \
	  indexxi.f juliam.f  \
	  matmult1.f matmult2.f matmult3.f mdian1.f \
	  normlz.f ran.f redist.f \
	  resstat_FDD.f scopy.f sdc2.f setorg.f \
	  snrm2.f sort.f sorti.f sscal.f \
	  svd.f tiddid.f trialsrc_FDD_shot.f trimlen.f \
	  vmodel.f RaySPDR2new.f  \
          getinpSPDR.f getdata_SPDR.f \
          dtres_FDD_lm5.f weighting_FDD.f lsfitHFDD_lsqr_lm5.f \
	  get_dims.f add_sta.f find_id2.f \
	  surfdisp96.f 
CSRCS	= atoangle_.c atoangle.c datetime_.c hypot_.c rpad_.c \
          sscanf3_.c transform_r_gfortran.c
F90SRCS = lsmrDataModule.f90 lsmrblasInterface.f90 lsmrblas.f90\
          lsmrModule.f90 delsph.f90 gaussian.f90
OBJS	= $(F90SRCS:%.f90=%.o) CalSurfG.o $(SRCS:%.f=%.o) $(CSRCS:%.c=%.o) 
INCLDIR	= ./include

CFLAGS = -O3 -I$(INCLDIR) -m64 -mcmodel=medium

# Flags for GNU g77 compiler
#FFLAGS	= -O -I$(INCLDIR) -fno-silent -Wall -ffixed-line-length-none -fbounds-check -m64
#FFLAGS = -O -I$(INCLDIR) -fno-silent -Wall -ffixed-line-length-none -m64
#FFLAGS  = -O3 -I$(INCLDIR) -implicit -ffixed-line-length-none -ffloat-store -W  -fbounds-check -m64 -mcmodel=medium
FFLAGS  = -O3 -I$(INCLDIR) -ffixed-line-length-none -ffloat-store -W  -m64 -mcmodel=medium
#FFLAGS  = -O -I$(INCLDIR) -implicit -ffixed-line-length-none -ffloat-store -W  -m64  -fbounds-check -mcmodel=medium
# Flags for SUN f77 compiler
#FFLAGS	= -O -I$(INCLDIR)
#FFLAGS	= -C -g -e -I$(INCLDIR)
#FFLAGS	= -O -e -I$(INCLDIR)
# Following line needed on HP-UX (hasn't been tested, though).
#LDFLAGS	= +U77
#LDFLAGS         = -O -m64

LDFLAGS         = -O3 -m64

all: $(CMD) 


$(CMD): $(OBJS)
	$(FC) -fopenmp $(LDFLAGS) $(OBJS) $(LIBS) -o $@
%.o: %.f90
	$(FC) $(FFLAGS) -c $(@F:.o=.f90) -o $@
CalSurfG.o:CalSurfGnew.f90                                                 
	    $(FC) -fopenmp $(FFLAGS) -c $< -o $@
%.o: %.f
	$(FC) $(FFLAGS) -c $(@F:.o=.f) -o $@


clean:
	-rm -f $(CMD) *.o core a.out *.fln junk *mod

