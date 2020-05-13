#!/bin/bash

echo "slurm host is"
echo $SLURMD_NODENAME
echo "slurm queue is"
echo $SLURM_JOB_PARTITION
echo "slurm working directory absolute is"
echo $SLURM_SUBMIT_DIR
echo "slurm batch id"
echo $SLURM_JOB_ID
echo "slurm job name is"
echo $SLURM_JOB_NAME
echo "GATOR directory is"
echo $gatordir

/bin/echo "sourcing " $gatordir/.bashrc
source $gatordir/.bashrc 


mkdir -p $gatordir/slurm_tmpfiles/$SLURM_JOB_ID
cd $gatordir/slurm_tmpfiles/$SLURM_JOB_ID

echo "$binary $macro $gatordir/slurm_tmpfiles/$SLURM_JOB_ID/$outfilename > $logfilename"
echo "cp ./$outfilename $outdir"
$binary "$macro" $gatordir/slurm_tmpfiles/$SLURM_JOB_ID/"$outfilename" > "$logfilename"


cp -p $gatordir/slurm_tmpfiles/$SLURM_JOB_ID/"$outfilename" "$outdir"
chmod 750 "$outdir""$outfilename" 


cd ../
rm -rf $gatordir/slurm_tmpfiles/$SLURM_JOB_ID

wait


