c   mxpari: maximum number of parameters to invert for.  This 
c           includes Vp and Vp/Vs nodes and P and S station 
c           corrections.  mxpari will generally be much lower
c           than maxpar because velocity nodes and station
c           corrections can be fixed. (Station corrections
c           are generally fixed to zero in the region of the
c           velocity inversion.)
      integer mxpari
      parameter(mxpari=500000)
c
c   maxpar: maximum number of potential parameters that could
c           be included in the inversion.  This includes all 
c           velocity nodes (includes both Vp and Vp/Vs) that
c           define the 3-D velocity model (nparv). Does not 
c           include edge nodes.
c           If station corrections are included in the inversion,
c           maxpar also includes stations (nparv+nsts or 
c           nparv + 2*nsts if P and S-P are used).
c           maxpar is set much larger than mxpari to allow
c           for assigning regional velocity (from prior
c           coarse inversions) values (fixed) in peripheral
c           areas where there is nil resolution.
      integer maxpar
      parameter(maxpar=500000)
c
c   maxnx: maximum number of nodes in x direction
      integer maxnx
      parameter(maxnx=150)
c   maxny: maximum number of nodes in y direction
      integer maxny
      parameter(maxny=150)     
c   maxnz: maximum number of nodes in z direction
      integer maxnz
      parameter(maxnz=50)     
c
c  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
c  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
c
c
c  common block variables:
c
c   control parameters
c

      integer iuses,invdel,iuseq,iGlobal
      common/contrl/  iuses,invdel,iuseq,iGlobal

c
c
c - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
c   velocity arrays
c
c   /vmod3d/
c    vel(nx,ny,2*nz)     ! 1st half is P velocity, 2nd half is S velocity
      
      integer maxnz2
      parameter(maxnz2=maxnz*2)
c
      integer nx, ny, nz, nxg, nyg, nzg
      real bld,xn(maxnx),yn(maxny),zn(maxnz),
     *     vel(maxnx,maxny,maxnz2),vpvs(maxnx,maxny,maxnz),
     *     qval(maxnx,maxny,maxnz), velg(360,360,1000),
     *     gxn(360), gyn(360), gzn(500)
      common/vmod3d/bld,nx,ny,nz,xn,yn,zn,nxg,nyg,nzg,gxn,gyn,gzn,
     *  vel,vpvs,velg,
     *  qval
c
c   /locate/
c   ixkms: size of map in x direction.  The distance between 
c            furthest nodes.  This will be in units of km if bld=1.0 
c            or in units of 0.1km if bld=0.1
      integer ixkms
      parameter(ixkms=200000)
c   iykms=size of map in y dir.
      integer iykms
      parameter(iykms=200000)
c   izkms=size of map in z dir.
      integer izkms
      parameter(izkms=200000)
c
      real xl, yl, zl, gxl, gyl, gzl
      integer ixloc(ixkms), iyloc(iykms), izloc(izkms)
      integer gixloc(ixkms), giyloc(iykms), gizloc(izkms)
      common/locate/ xl,yl,zl,ixloc,iyloc,izloc,gxl,gyl,gzl,
     &               gixloc,giyloc,gizloc
c
c
c - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
c  inversion arrays
c
c
cfhdmep nparpi, nparsi, nrowp,nrows,nrowst added here

      character*1 cnode(maxpar)
      integer nz2, nx1, ny1, nz1,nparvi,npari,inf
      integer nfix(maxpar),ndexfx(maxpar), mdexfx(mxpari),
     *          nparv,npar,nodes, nxy,nx2,nxy2,
     *          nodes2,nparpi,nparsi,
     *          imerge(maxpar),jequal(maxpar),ltype(maxpar),
     *          infl,imast,ilink, nfixst(maxpar)
      real dtm(mxpari),hit(maxpar),hitall(maxpar)

      common/modinv/ nz2,nx1,dtm,
     *  ny1,nz1,nparvi,npari,inf,nfix,ndexfx,
     *  mdexfx,nparv,npar,nodes,nxy,hit,hitall,
     *  nx2,nxy2,nodes2,
     *  nparpi,nparsi,cnode,
     *  imerge,jequal,ltype,infl,imast,ilink,
     *  nfixst
c  above line added cht 1998
c
c
      integer MAXSEG1, nrp, pl
      parameter(MAXSEG1=100000)
      real rp(3,MAXSEG1)
      common/rpath/ rp,nrp, pl

c - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        integer msg
        parameter(msg = 10000)

        integer np1, np15, npcom, nlayer
        parameter(np1=6379,np15=449,npcom=100000,nlayer=16)


